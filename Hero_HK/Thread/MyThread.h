#include<thread>
#include<mutex>
#include<condition_variable>
#include<iostream>
#include<vector>
#include<chrono>
#include<opencv2/opencv.hpp>
#include"../Armor/ArmorDetect.h"
#include "../PNP_Distance/PNP_Distance.h"
#include"../HaikangCamera/HaikangCameraRGB.h"
#include"../SerialPort/SerialPort.h"
#include"../Analaze_Data/Analaze_Data.h"
using namespace std;
using namespace cv;

#ifndef HERO_HK_MYTHREAD_H
#define HERO_HK_MYTHREAD_H


class MyThread
{
public:
    //初始化线程：用来打开串口、PNP解算的初始化
    MyThread();
    //视频线程
    void VideoThread();
    //相机读取线程
    void CamerThread();
    //装甲板识别线程
    void decThread();
    //串口发送线程
    void SendPortThread();
    //串口接收线程
    void ReceivePortThread();

private:
    ArmorDetect detect; //装甲板检测类
    PNP_Distance angleSolver; //角度解算类
    HaiKangCameraRGB HaiKang;//相机
    SerialPort serialPort;//串口通信
    Analyze_Data analyzeData; //数据分析


    Mat frame;
    Mat showImg;

    double fps;
    mutex mutexLock;
    bool isContinue=true;
    condition_variable DetectCondition,Condition; //条件变量：装甲板检测，视频/相机的图片载入
public:
    Color enemy_Color;


};


//读视频
void ReVideo(Color &enemy_Color);
//读相机
void ReCamera(Color &enemy_Color);

//
#endif //HERO_HK_MYTHREAD_H
