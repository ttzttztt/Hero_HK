#include "../Struct.h"
#ifndef HERO_HK_ARMORDETECT_H
#define HERO_HK_ARMORDETECT_H

//敌方装甲板颜色
enum Color
{
    BLUE=0,
    RED=1
};


// 自瞄模式
enum DetectorState
{
    LIGHTS_NOT_FOUND = 0,
    LIGHTS_FOUND = 1,
    ARMOR_NOT_FOUND = 2,
    ARMOR_FOUND = 3
};


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

    // 判断某个装甲板是否合适(是否能够构成一个装甲板)
    bool isSuitableArmor() const;

public:
    LightBar l_light, r_light; // 定义装甲板的左右灯条
    int l_index, r_index; // 左右灯条的下标(默认为-1，仅作为ArmorDetector类成员时生效)
    int armorNum;  // 存储SVM识别后装甲板上的数字（用SVM识别得到）
    vector<Point2f> armorVertices;  // 存储装甲板的四个顶点 左下 左上 右上 右下

    Point2f center;	// 存储装甲板的中心
    Rect armorRect;  // 存储装甲板的矩形所获取的roi区域
    float armorAngle;// 存储装甲板角度(灯条角度的平均值)
    Mat armorImg;	// 装甲板的图片（透射变换后的装甲板图片）
    double tx;
    double ty;
    double tz;
};


//装甲板识别类
class ArmorDetect
{
public:
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
    //装甲板识别集成函数
    void run(Mat&src);

private:
    Mat Image;
    Mat BinImage;
    Color enemyColor;
    vector<LightBar> lights; //找到所有可能的灯条
    vector<ArmorBox> armors; //找到所有可能的装甲板
    DetectorState state;
};


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
        color_threshold=210;
        bright_threshold=90;

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





#endif //HERO_HK_ARMORDETECT_H
