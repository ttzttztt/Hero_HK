#include <Eigen/Core>
#include<opencv2/core/eigen.hpp>
#include"../Armor/ArmorDetect.h"

class PNP_Distance
{
private:
    Mat cameraMatrix;//相机的内参矩阵
    Mat distCoeffs;//相机的畸变系数

    //大小装甲板高度与宽度
    const float kSmallArmorWidth = 135;
    const float kSmallArmorHeight = 55;
    const float kLargeArmorWidth = 230;
    const float kLargeArmorHeight = 55 ;

    //大小装甲板位置xyz
    vector<Point3f> small_points;
    vector<Point3f> large_points;

    //用于距离滤波的参数和变量
    int old_flag = 0;   //表示第n-2个数据到第n-1个数据的变化趋势，加为1，减为0
    int new_flag = 0;   //表示第n-1个数据到第n个数据的变化趋势，加为1，减为0
    double old_data = 0;//上一帧的距离
    int num_x = 0;      //一个过渡值，对于同方向变化量大的数据，num_x越大
    float k_x = 0.2;    //表示对新读入的数据的信任度，取值范围0-1

    const double Threshold_1 = 100;
    const double Threshold_2 = 8;

    //旋转向量和平移向量
    Mat rvec, tvec; //rvec表示世界坐标系中的地i个坐标周方向的单位向量在

    //计算输出的参数
    float y_yaw;            //yaw值
    float x_pitch;          //pitch值
    double distance;        //距离

    //目标装甲板
    ArmorBox BestArmor;

    double BULLET_SPEED;
    double GUN_CAM_DISTANCE_Y;
    vector<Point2f> targetContour ;
    Point2f targetCenter;
    ArmorType targetType ;

public:
    PNP_Distance() = default;
    void setData();//设置参数:相机内参，大小装甲板2D，3D位置

    //Pnp解算:求解出旋转向量和平移向量
    void TosolvePnP();

    //低通滤波
    double Di_filter(double);

    //计算装甲板的pitch和yaw
    void P4P_solver();     //P4P method（使用相机成像原理）
    void PinHole_solver(); // PinHole method（使用小孔成像原理）

    void setBulletSpeed(int bulletSpeed);

    void setTarget(vector<Point2f> contoursPoints, Point2f centerPoint, ArmorType type);

    void compensateAngle();


    void compensateOffset();


    void compensateGravity();


    void getAngle(vector<Point2f> & contourPoints, Point2f centerPoint, ArmorType type, double & yaw, double & pitch, double & evaluateDistance);

    float yaw();
    float pitch();
    double dist();
};


