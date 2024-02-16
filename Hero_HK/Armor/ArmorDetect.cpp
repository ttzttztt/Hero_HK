#include"ArmorDetect.h"


//初始化装甲板识别类的参数
ArmorParam armorParam=ArmorParam();

//载入原图像并进行处理
void ArmorDetect::setImage(Mat&src,Color color)
{
    src.copyTo(Image);
    BinImage=Mat::zeros(src.size(),CV_8UC1);

    uchar*pdata=(uchar*)Image.data;
    uchar*qdata=(uchar*)BinImage.data;
    int ImageSize=Image.rows*Image.cols;
    if (enemyColor == RED)
    {
        for (int i = 0; i < ImageSize; i++)
        {
            if (*(pdata + 2) - *pdata > armorParam.color_threshold)
                *qdata = 255;
            pdata += 3;
            qdata++;
        }
    }
        // 提取蓝色灯条
    else if (enemyColor == BLUE)
    {
        for (int i = 0; i < ImageSize; i++)
        {
            if (*pdata - *(pdata + 2) > armorParam.color_threshold)
                *qdata = 255;
            pdata += 3;
            qdata++;
        }
    }


    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(9,9)); // 矩形内核形状，(3, 3)内核尺寸
    dilate(BinImage, BinImage, kernel); // 对BinImage进行膨胀操作，使灯条区域更加平滑

    imshow("BinImage",BinImage);
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


// 针对游离灯条导致的错误装甲板进行检测和删除
void eraseErrorRepeatArmor(vector<ArmorBox>& armors)
{
    int length = armors.size();
    vector<ArmorBox>::iterator it = armors.begin();		// 迭代检测到的装甲板
    // 根据同一位置上的灯条由于游离灯条可能构造出其他错误的装甲板，因此根据灯条错位度角删除错位角大的装甲板
    for (size_t i = 0; i < length; i++) {
        for (size_t j = i + 1; j < length; j++)
        {
            if (armors[i].l_index == armors[j].l_index ||
                armors[i].l_index == armors[j].r_index ||
                armors[i].r_index == armors[j].l_index ||
                armors[i].r_index == armors[j].r_index)
            {
                // .erase() 删除所迭代到的错误装甲板
                armors[i].getDeviationAngle() > armors[j].getDeviationAngle() ? armors.erase(it + i) : armors.erase(it + j);
            }
        }
    }
}

//匹配装甲板
void ArmorDetect::matchArmors()
{
    for(int i=0;i<lights.size();i++)
    {
        for(int j=i+1;j<lights.size();j++)
        {
            ArmorBox armor=ArmorBox(lights[i],lights[j]);
            // 利用ArmorBox类中的子函数判断这个装甲板是否是一个合适的装甲板
            if (armor.isSuitableArmor()) // 如果是合适的装甲板，则设置其他装甲板信息
            {
                armor.l_index = i; // 左灯条在lights数组中的下标
                armor.r_index = j; // 右灯条在lights数组中的下标
                armors.emplace_back(armor); // 将识别到的装甲板存入armors数组中
            }
        }
        eraseErrorRepeatArmor(armors);// 删除游离灯条导致的错误装甲板
    }
}


void ArmorDetect::run(Mat&Img)
{
    setImage(Img,BLUE);
    lights.clear();
    armors.clear();
    findLights();
    showLights(Img,lights);
    matchArmors();
    showArmors(Img,armors);
}



