#include"ArmorDetect.h"


//初始化装甲板识别类的参数
ArmorParam armorParam=ArmorParam();

//初始化装甲板识别类
ArmorDetect::ArmorDetect()
{
    state=LIGHTS_NOT_FOUND;
}


//析构函数装甲板识别类
ArmorDetect::~ArmorDetect(){}


//载入原图像并进行处理
void ArmorDetect::setImage(Mat&src,Color color)
{
    enemyColor=color;
    Mat green =Mat::zeros(src.size(),CV_8UC1);
    src.copyTo(Image);
    BinImage=Mat::zeros(src.size(),CV_8UC1);
    vector<Mat> channels;
    split(Image,channels);


    if (enemyColor == RED)
    {
        subtract(channels[2],channels[0],BinImage);
        threshold(BinImage,BinImage,armorParam.color_threshold,255,THRESH_BINARY);
        subtract(channels[1],channels[0],green);//g-r

    }
        // 提取蓝色灯条
    else if (enemyColor == BLUE)
    {
        subtract(channels[0],channels[2],BinImage);
        threshold(BinImage,BinImage,armorParam.color_threshold,255,THRESH_BINARY);
        subtract(green,channels[0],green); //g-b

    }

    threshold(green,green,50,255,THRESH_BINARY_INV);
    bitwise_and(BinImage,green,BinImage);
    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(3,3)); // 矩形内核形状，(3, 3)内核尺寸
    morphologyEx(BinImage,BinImage,MORPH_CLOSE,kernel);
//    cvtColor(src,green,COLOR_RGB2GRAY);
//    threshold(green,BinImage,150,255,THRESH_BINARY);


}



// 检测所有可能的灯条
void ArmorDetect::findLights()
{
    vector<vector<Point>> lightContours;  //定义候选灯光轮廓
    Mat contourImg;
    BinImage.copyTo(contourImg); //将图像复制到contourImg，防止findContours改变roiImg
    findContours(contourImg, lightContours, 0, 2); //CV_RETR_EXTERNAL = 0, CV_CHAIN_APPROX_SIMPLE = 2       最耗时的操作，需要进行优化
    RotatedRect lightRect;  // 拟合椭圆来的灯条旋转矩形
    LightBar light;  // 定义临时灯条

    for (const auto& lightContour : lightContours)
    {	// 迭代lightContours
        if (lightContour.size() < 6)	// 如果轮廓点数小于6，不可拟合椭圆
            continue;
        if (contourArea(lightContour) < armorParam.min_area)	// 面积筛选，滤去小的发光点
            continue;

        lightRect = fitEllipse(lightContour);	// 拟合椭圆
        light = LightBar(lightRect);			// 构造为灯条

        if (abs(light.angle) > armorParam.max_angle)	// 角度筛选，滤去一些竖直偏角偏大的发光点
            continue;

        lights.emplace_back(light);		// 在vector容器的尾部添加一个元素
    }
    // 灯条少于两条则设置状态为没找到灯条（要有超过两条的灯条才可以构造成一个装甲板）
    if (lights.size() < 2) {
        state = LIGHTS_NOT_FOUND;
        return;
    }

    // 依据灯条中心从左往右排序
    sort(lights.begin(), lights.end(), [](LightBar& a1, LightBar& a2) { return a1.center.x < a2.center.x; });
    state = LIGHTS_FOUND;
    return;
}



//装甲板识别集成函数
void ArmorDetect::run(Mat&Img,Color enemy_Color)
{
    //得到击打颜色

    //预处理图像
    setImage(Img,enemy_Color);
    imshow("BinImage",BinImage);

    //清除上一帧找到的灯条和装甲板
    lights.clear();
    armors.clear();

    //检测所有可能的灯条
    findLights();
//    showLights(Img,lights);


    if(state==LIGHTS_FOUND)
    {
        //对图像进行处理:将图像二值化，将数字凸显出来
        classifier.LoadImage(Img);
//        imshow("warpPerspective_src",classifier.warpPerspective_src); //二值图

        //装甲板匹配
        matchArmors();
//        showArmors(Img,armors);


        if(state==ARMOR_FOUND)
        {
            //找到最佳打击装甲板
            setTargetArmor();
        }
        else if(state==ARMOR_NOT_FOUND)
        {
            targetArmor=ArmorBox();
        }


    }

}

//载入SVM模型,调用SVM类中的loadSvmModel函数
void ArmorDetect::loadSVM()
{
    classifier.loadSvmModel("../123svm.xml",Size(40,40));
}





