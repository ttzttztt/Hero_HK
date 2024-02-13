#include<thread>
#include<mutex>
#include<condition_variable>
#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

#ifndef HERO_HK_MYTHREAD_H
#define HERO_HK_MYTHREAD_H


class MyThread
{
public:
    void VideoThread();
private:
    Mat frame;
    bool isContinue=true;
    mutex mutexLock;
};


//读视频
void ReVideo();
//读相机
void ReCamera();

//
#endif //HERO_HK_MYTHREAD_H
