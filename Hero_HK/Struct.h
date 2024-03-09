#include<thread>
#include<mutex>
#include<condition_variable>
#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include"sophus/se3.hpp"
#include"sophus/so3.hpp"

#include <cstdio>
#include <cstdint>
#include <fcntl.h>
#include <termios.h>
#include <complex>
#include <unistd.h>
#include <opencv2/core/types.hpp>


#include <cstdio>

using namespace std;
using namespace cv;
using namespace cv::ml;
using namespace Sophus;

#ifndef STRUCT_H
#define STRUCT_H
//敌方装甲板颜色
enum Color
{
    BLUE=0,
    RED=1
};


//装甲板检测状态
enum DetectorState
{
    LIGHTS_NOT_FOUND = 0,
    LIGHTS_FOUND = 1,
    ARMOR_NOT_FOUND = 2,
    ARMOR_FOUND = 3
};

//装甲板类型
enum ArmorType
{
    SMALL_ARMOR=0,   //步兵、英雄
    BIG_ARMOR=1      //哨兵
};

//串口发送数据长度
#define write_dataLen 13
//串口接收数据长度
#define Read_dataLen 26


#endif //STRUCT_H


