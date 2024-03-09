#include "PNP_Distance.h"


void PNP_Distance::setData()
{
    GUN_CAM_DISTANCE_Y=0.0;

    //相机的内参矩阵
    array<double, 9> matrix;
    matrix[0]=2406.05915203876;
    matrix[1]=0;
    matrix[2]=640.682242246552;
    matrix[3]=0;
    matrix[4]=2409.33232600473;
    matrix[5]=269.487011771147;
    matrix[6]=0;
    matrix[7]=0;
    matrix[8]=1.0000;

    //相机的畸变系数
    array<double, 5>  coeffs;
    coeffs[0]=-0.0795432999746667;
    coeffs[1]= 0.388376048060758;
    coeffs[2]= 0;
    coeffs[3]=0.371029422180722;
    coeffs[4]=0;

    //获取相机参数
    //相机内参矩阵
    cameraMatrix = Mat(3, 3, CV_64F, const_cast<double *>(matrix.data())).clone();
    //相机畸变参数
    distCoeffs = Mat(1, 5, CV_64F, const_cast<double *>(coeffs.data())).clone();

    //大小装甲板的高度与宽度的一半
    float s_h_x = kSmallArmorWidth / 2.0f;//small half x
    float s_h_y = kSmallArmorHeight / 2.0f;//small half y
    float l_h_x = kLargeArmorWidth / 2.0f;
    float l_h_y = kLargeArmorHeight / 2.0f;

    //设置大小装甲板点位
    //相对于相机坐标系的装甲板位置
    small_points.emplace_back(Point3f(-s_h_x, s_h_y, 0));//左上角
    small_points.emplace_back(Point3f(-s_h_x, -s_h_y, 0));//左下角
    small_points.emplace_back(Point3f(s_h_x, -s_h_y, 0));//右下角
    small_points.emplace_back(Point3f(s_h_x, s_h_y, 0));//右上角

    large_points.emplace_back(Point3f(-l_h_x, l_h_y, 0));//左上角
    large_points.emplace_back(Point3f(-l_h_x, -l_h_y, 0));//左下角
    large_points.emplace_back(Point3f(l_h_x, -l_h_y, 0));//右下角
    large_points.emplace_back(Point3f(l_h_x, l_h_y, 0));//右上角
}


//低通滤波的原理：基于数据变化趋势，通过限制数据变化速率来平滑数据。
//减小数据的突变和噪声，使输入数据更加平滑和稳定。
double PNP_Distance::Di_filter(double new_data)
{
    if(old_data == 0)//判断old_data是否为初始值，表示第一次滤波
    {
        old_data = new_data;
        return old_data;
    }
    if (new_data - old_data > 0 )       //计算方向：大于0，表示变化方向为正。
        new_flag = 1;
    else new_flag = 0;
    if (new_flag == old_flag)           //变化同向
    {
        if (abs (new_data - old_data) > Threshold_1)    //变化很大则num增大
            num_x += 5;
        if (num_x >= Threshold_2)       //变化持续同向且一直变化很大则k_x增大
            k_x += 0.2;
    }
    else                //变化反向
    {
        num_x = 0;
        k_x = 0.2;
        old_flag = new_flag;
    }
    if (k_x > 0.95)  k_x = 0.95;    //系数限幅
    new_data = (1-k_x) * old_data + k_x * new_data;   //计算答案

    old_data = new_data;        //更新old_data

    return new_data;
}


void PNP_Distance::TosolvePnP()
{
    vector<Point2f> armorP;
    //获取装甲板各点位置
    for(int i=0;i<4;i++)
    {
        armorP.emplace_back(targetContour[i]);
    }

    // Solve pnp

    vector<Point3f> object_points = targetType == SMALL_ARMOR
                                    ? small_points : large_points;

    bool success = solvePnP(
            object_points, //三维空间坐标位置
            armorP, //二维空间坐标位置
            cameraMatrix, distCoeffs, //相机内参矩阵 相机畸变参数
            rvec, tvec, //输出的旋转向量 输出的平移向量  ：  使坐标点从世界坐标系 旋转/平移 到相机坐标系
            false,
            SOLVEPNP_AP3P);//SOLVEPNP_P3P
    if (success)
    {//获取坐标位置
        double tx = tvec.at<double>(0,0);
        double ty = tvec.at<double>(1,0);
        double tz = tvec.at<double>(2,0);

        distance=sqrt(tx*tx+ty*ty+tz*tz);

    }


    P4P_solver();
//    if(distance>5000) //目标距离大于5米，使用小孔成像,来计算pitch和yaw
//    {
//        PinHole_solver();
//    }
//    else  //目标距离小于5米，使用相机成像原理,来计算pitch和yaw
//    {
//        P4P_solver();
//    }
}

// P4P method（使用相机成像原理）
void PNP_Distance::P4P_solver()
{
    double x_pos = tvec.at<double>(0, 0);
    double y_pos = tvec.at<double>(1, 0);
    double z_pos = tvec.at<double>(2, 0);

    double tan_pitch = y_pos / sqrt(x_pos*x_pos + z_pos * z_pos);
    double tan_yaw = x_pos / z_pos;
    x_pitch = -atan(tan_pitch) * 180 / CV_PI;
    y_yaw = atan(tan_yaw) * 180 / CV_PI;
}


// PinHole method（使用小孔成像原理）
void PNP_Distance::PinHole_solver()
{
    //  相机内参矩阵
    double fx = cameraMatrix.at<double>(0, 0);
    double fy = cameraMatrix.at<double>(1, 1);
    double cx = cameraMatrix.at<double>(0, 2);
    double cy = cameraMatrix.at<double>(1, 2);

    Point2f pnt;
    vector<cv::Point2f> in;
    vector<cv::Point2f> out;
    in.push_back(BestArmor.center);

    /*
        * Goal: 将拍摄的图像矫正为正常的视角，便于检测
        * undistortPoints() 根据相机参数和观测到点坐标位置计算实际坐标位置
    */
    undistortPoints(in, out, cameraMatrix, distCoeffs, noArray(), cameraMatrix);
    // .front() 用于获取 vector<cv::Point2f> 数组中的第一个
    pnt = out.front();

    /*
        * Goal: 去畸变后的比值
        * Formula: tan<pitch> = X / Z = (x<screen> - cx) / fx
        *		   tan<yaw> = Y / Z = (y<screen> - cy) / fy
    */
    double rxNew = (pnt.x - cx) / fx;
    double ryNew = (pnt.y - cy) / fy;


     x_pitch = -atan(ryNew) / CV_PI * 180;
     y_yaw = atan(rxNew) / CV_PI * 180;
}


void PNP_Distance::setBulletSpeed(int bulletSpeed)
{
    BULLET_SPEED = bulletSpeed;
}

void PNP_Distance::setTarget(vector<Point2f> contourPoints, Point2f centerPoint, ArmorType type)
{
    targetContour = contourPoints;
    targetCenter = centerPoint;
    targetType = type;
}


void PNP_Distance::compensateAngle()
{
    compensateOffset();
    compensateGravity();
}

void PNP_Distance::compensateOffset()
{
    float camera_target_height = distance * sin(x_pitch / 180 * CV_PI);
    float gun_target_height = camera_target_height + GUN_CAM_DISTANCE_Y;
    float gun_pitch_tan = gun_target_height / (distance * cos(x_pitch / 180 * CV_PI));
    x_pitch = atan(gun_pitch_tan) / CV_PI * 180;
}

void PNP_Distance::compensateGravity()
{
    float compensateGravity_pitch_tan = tan(x_pitch/180*CV_PI) + (0.5*9.8*(distance / BULLET_SPEED)*(distance / BULLET_SPEED)) / cos(x_pitch/180*CV_PI);
    x_pitch = atan(compensateGravity_pitch_tan)/CV_PI*180;
}

void PNP_Distance::getAngle(vector<Point2f>& contourPoints,Point2f cenerPoint, ArmorType type, double & yaw, double & pitch, double & evaluateDistance)
{
    setTarget(contourPoints, cenerPoint, type);
    TosolvePnP();
    //compensateAngle();
    yaw = y_yaw;
    pitch = x_pitch;
    evaluateDistance = distance;
    //cout<<"yaw:   "<<yaw<<"  "<<"pitch:   "<<pitch<<"distance:   "<<evaluateDistance<<endl;
}

float PNP_Distance::yaw()
{
    return y_yaw;
}

float PNP_Distance::pitch()
{
    return x_pitch;
}

double PNP_Distance::dist()
{
    return distance;
}





