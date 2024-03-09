#include<iostream>
#include <cstdio>
#include <cstdint>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "../Struct.h"
using namespace std;



class SerialPort
{
public:
    int num = 0;
    SerialPort()=default;
    bool OpenSerialPort();//开启串口
    // 重启串口
    void restart_serial();
    // 发送数据
    void send_data(uint8_t a[]);
    // 接收数据
    uint8_t* read_data();
    // 关闭串口
    void close_port();
    int fd=-1;//fd为打开的终端文件描述符

private:
    string file_name_="/dev/ttyUSB";//设置串口名字

};
