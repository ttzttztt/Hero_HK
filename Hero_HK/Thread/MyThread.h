#include<thread>
#include<mutex>
#include<condition_variable>
#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include"../Armor/ArmorDetect.h"
using namespace std;
using namespace cv;

#ifndef HERO_HK_MYTHREAD_H
#define HERO_HK_MYTHREAD_H


class MyThread
{
public:
    //视频线程
    void VideoThread();
    //装甲板识别线程
    void decThread();
private:
    Mat frame;
    mutex mutexLock;
    condition_variable DetectCondition,Condition; //条件变量：装甲板检测，视频/相机的图片载入
};


//读视频
void ReVideo();
//读相机
void ReCamera();

//
#endif //HERO_HK_MYTHREAD_H
