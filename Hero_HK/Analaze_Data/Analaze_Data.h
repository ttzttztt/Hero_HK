#include <cstdio>
#include <cstdint>
#include<iostream>
#include <fcntl.h>
#include <termios.h>
#include <complex>
#include <unistd.h>
#include <opencv2/core/types.hpp>
#include "../Struct.h"

using namespace std;

void float2u8Arry(uint8_t *u8Arry, float *floatdata);
float u8Arry2float(uint8_t *data);


//用于分析串口传入的数据
class Analyze_Data
{
public:
    uint8_t head=0x80,end=0x7F;//用于了解哪里开始是头 哪些结束是尾
    cv::Point3_<float> position;
    int color=-1;//颜色
    int number=-1;//目标序号
    int type = 0;//击打装甲板的类型 0小 1大

    double V=14;//子弹速度
    double K=0.0046;//风阻 0.0046
    double M = 0.003;//质量 43da 03xiao
    double G = 9.78;//重力加速度
    int model = 0;//识别模式
    int speedmodel = 0;//速度模式
    int auto_aim_state = 0;//预测模式
    int PortIsOpen =0;

public:
    //获取的pit yaw
    float SPit = 0;
    float SYaw = 0;

private:
    float myPitch=0;
    float myYaw=0;
public:
    bool isSend=false;//判断是否在发送

    Analyze_Data()=default;

    /*
     *发送数据封装
     */
    unsigned char * TransData(float myPitch,float myYaw,double dis);
    /*
     *分析数据
     */
    void setData(uint8_t* c);

    Color getcolor();

    int getNumber();

    void setPoint(cv::Point3_<float> point3,int type);

    cv::Point3_<float> getPosition();
    int getColor();
    void analyze();
    float getPit();
    float getYaw();

    double getPitch(double x,double y);

    void SetPortIsOpen();



};