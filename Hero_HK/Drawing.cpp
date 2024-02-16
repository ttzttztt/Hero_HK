#include"Armor/ArmorDetect.h"

// 在图像中显示所有找到的灯条（LightBar）
void ArmorDetect::showLights(Mat& image, const vector<LightBar>& lights)
{
    Mat lightDisplay;	// 用于显示灯条的图像
    image.copyTo(lightDisplay);		// 获取源图像的拷贝，以防对原图像进行修改

    // 如果找到了灯条
    if (!lights.empty())
    {
        putText(lightDisplay, "LIGHTS FOUND!", Point(100, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255), 1, 8, false); // 显示大标题 “LIGHTS FOUND!”
        // 画出所有灯条轮廓以及灯条中心和中心位置坐标
        // auto相当于iterator（迭代）
        for (auto light : lights)
        {
            Point2f lightVertices[4];
            light.lightRect.points(lightVertices);	// 灯条旋转矩形的四个顶点
            // 画出所有灯条的轮廓
            for (size_t i = 0; i < 4; i++)
            {
                line(lightDisplay, lightVertices[i], lightVertices[(i + 1) % 4], Scalar(255, 0, 255), 1, 8, 0);
            }

            // 画出灯条中心
            circle(lightDisplay, light.center, 2, Scalar(0, 255, 0), 2, 8, 0);

            // 显示灯条的中心坐标点
            putText(lightDisplay, to_string(int(light.center.x)), light.center, FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 1, 8, false);
            putText(lightDisplay, to_string(int(light.center.y)), light.center + Point2f(0, 15), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 1, 8, false);
        }
    }
        // 如果没找到灯条
    else
    {
        putText(lightDisplay, "LIGHTS NOT FOUND!", Point(100, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 1, 8, false);// 显示大标题 “LIGHTS NOT FOUND!”
    }

    // 显示结果图
    imshow("Lights Monitor", lightDisplay);
}



// 在图像中显示所有找到的装甲板（Armors）
void ArmorDetect::showArmors(Mat& image, const vector<ArmorBox>& armors)
{
    Mat armorDisplay; // 展示装甲板的图像
    image.copyTo(armorDisplay); // 获取源图像的拷贝，以防对原图像进行修改

    // 如果找到了装甲板
    if (!armors.empty())
    {
        putText(armorDisplay, "ARMOR FOUND!", Point(100, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 1, 8, false); // 显示大标题 “ARMOR FOUND!”
        string name = "ARMOR FOUND!";
        putText(armorDisplay, name, Point(100, 500), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 1, 8, false);// 显示灯条长度
        // 画出所有装甲板的顶点边以及中心和中心位置坐标
        for (auto armor : armors)
        {
            // 画中心
            circle(armorDisplay, armor.center, 2, Scalar(0, 255, 0), 2);
            // 画出所有装甲板边框
            for (size_t i = 0; i < 4; i++)
            {
                line(armorDisplay, armor.armorVertices[i], armor.armorVertices[(i + 1) % 4], Scalar(255, 255, 255), 2, 8, 0);
            }
            // 显示中点坐标以及SVM识别出的装甲板上的数字
            putText(armorDisplay, to_string(int(armor.center.x)), armor.center, FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
            putText(armorDisplay, to_string(int(armor.center.y)), armor.center + Point2f(0, 15), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 255), 1, 8, false);
            //putText(armorDisplay, to_string(int(armor.type)), armor.center + Point2f(15, 30), FONT_HERSHEY_PLAIN, 1, Scalar(255, 255, 255), 1, 8, false);
        }
//        // 画出最佳击打装甲板轮廓
//        for (size_t i = 0; i < 4; i++)
//        {
//            line(armorDisplay, targetArmor.armorVertices[i], targetArmor.armorVertices[(i + 1) % 4], Scalar(255, 255, 0), 2, 8, 0);
//        }
    }
        // 如果没找到装甲板
    else
    {
        putText(armorDisplay, "ARMOR NOT FOUND!", Point(100, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 255), 1, 8, false);// 显示大标题 “ARMOR NOT FOUND!”
    }

    // 显示结果图
    imshow("Armor Monitor", armorDisplay);
}
