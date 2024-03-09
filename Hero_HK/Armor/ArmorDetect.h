#include "../Struct.h"
#ifndef HERO_HK_ARMORDETECT_H
#define HERO_HK_ARMORDETECT_H



//装甲板识别类的参数
struct ArmorParam
{
    int color_threshold; //通道相减 二值化阈值
    int bright_threshold; //HSV  二值化阈值

    float min_area;//灯条允许的最小面积
    float max_angle;// 灯条允许的最大偏角

    // 匹配装甲板
    float max_angle_diff; // 左右两个灯条之间允许的最大角度差
    float max_lengthDiff_ratio; // 左右两个灯条之间允许的最大长度差比值
    float max_deviation_angle; // 左右两灯条最大错位角(两灯条中心连线与水平线夹角)

    float max_x_diff_ratio;  // 灯条x方向最大位置差距
    float max_y_diff_ratio;  // 灯条y方向最大位置差距


    ArmorParam()
    {
        //200
        color_threshold=160;
        bright_threshold=10;

        min_area=30;
        max_angle=20;

        max_angle_diff = 8;
        max_lengthDiff_ratio = 0.5;
        max_deviation_angle = 10;

        max_y_diff_ratio = 0.5;
        max_x_diff_ratio = 4.2;
    }

};
//全局变量
extern ArmorParam armorParam;


//灯条的相关信息
class LightBar
{
public:
    RotatedRect lightRect; //灯条的旋转矩阵
    float length; // 灯条长度
    Point2f center; // 灯条中心
    float angle; //灯条角度
public:
    LightBar();
    LightBar(const RotatedRect & light);
    ~LightBar();
};


// 装甲板相关的数据信息
class ArmorBox
{
public:

    // 装甲板无参构造函数
    ArmorBox();

    // 装甲板有参构造函数
    // 参数：左右两个灯条
    ArmorBox(const LightBar& l_light, const LightBar& r_light);
    ~ArmorBox();

    // 获取装甲板左右灯条角度差
    float getAngleDiff() const;

    // 获取左右灯条长度差比值
    float getLengthRation() const;

    // 获取灯条错位度角(两灯条中心连线与水平线夹角)
    float getDeviationAngle() const;

    // 灯条位置差距 获取两灯条中心X方向差距比值
    float getDislocationX() const;

    // 灯条位置差距 获取两灯条中心Y方向差距比值
    float getDislocationY() const;

    // 判断某个装甲板是否合适(是否能够构成一个装甲板),上面函数的集成函数
    bool isSuitableArmor() const;

public:
    LightBar l_light, r_light; // 定义装甲板的左右灯条
    int l_index, r_index; // 左右灯条的下标(默认为-1，仅作为ArmorDetector类成员时生效)
    int armorNum;  // 存储SVM识别后装甲板上的数字（用SVM识别得到）
    vector<Point2f> armorVertices;  // 存储装甲板的四个顶点 左下 左上 右上 右下
    ArmorType type; //装甲板类型（大、小）
    Point2f center;	// 存储装甲板的中心
    Rect armorRect;  // 存储装甲板的矩形所获取的roi区域
    float armorAngle;// 存储装甲板角度(灯条角度的平均值)
    Mat armorImg;	// 装甲板的图片（透射变换后的装甲板图片）
    double tx; //目标装甲板的位置
    double ty; //目标装甲板的位置
    double tz; //目标装甲板的位置

};

//装甲板数字识别类
class ArmorNumclassifier
{
public:
    //无参构造函数
    ArmorNumclassifier();

    //析构函数
    ~ArmorNumclassifier();

    //载入SVM模型（识别装甲板数字）
    void loadSvmModel(const char* model_path,Size armorImgSize);

    //对图像进行处理:将图像二值化，将数字凸显出来
    void LoadImage(Mat & src);

    //利用投射变换得到装甲板图片
    void getArmorImage(ArmorBox & armor);

    //利用SVM实现装甲板数字识别
    void setArmorNum(ArmorBox & armor);

public:
    Ptr<cv::ml::SVM>svm; //SVM模型
    Mat p;  //载入到SVM中识别的矩阵
    Size armorImageSize; //SVM模型识别图片大小

    Mat warpPerspective_src; //投射变换的原图
    Mat warpPerspective_dst; //投射变换后生成的图像
    Mat warpPerspective_mat; //投射变换的变换矩阵
    Point2f srcPoints[4]; //投射变换原图像的点 左上 右上 右下 左下
    Point2f dstPoints[4]; //投射变换后目标图像的点 左上 右上 右下 左下
};



//装甲板识别类
class ArmorDetect
{
public:
    ArmorDetect();
    ~ArmorDetect();
    //载入原图像并进行处理
    void setImage(Mat & src,Color color);
    // 检测所有可能的灯条
    void findLights();
    // 在图像中显示所有找到的灯条（LightBar）
    void showLights(Mat& image, const vector<LightBar>& lights);
    // 将灯条拟合为装甲板
    void matchArmors();
    //在图像中显示所有找到的装甲板
    void showArmors(Mat & image, const vector<ArmorBox>& armors);
    //得到最佳打击装甲板
    void setTargetArmor();
    //装甲板识别集成函数
    void run(Mat&src,Color enemy_Color);
    //载入SVM模型,调用SVM类中的loadSvmModel函数
    void loadSVM();

public:
    Mat Image;
    Mat BinImage;
    Color enemyColor;
    int targetNum;
    vector<LightBar> lights; //找到所有可能的灯条
    vector<ArmorBox> armors; //找到所有可能的装甲板
    ArmorNumclassifier classifier;//载入数字识别 SVM类
    DetectorState state; //装甲板检测状态 ：灯条/装甲板是否被检测
    ArmorBox lastArmor; //上一帧的目标装甲板
    ArmorBox targetArmor; //当前帧对应的目标装甲板
};










#endif //HERO_HK_ARMORDETECT_H
