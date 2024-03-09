#include "SerialPort.h"

bool SerialPort::OpenSerialPort(){
    /*
        * 参数：file_name_为串口名称   模式选择
        * O_RDWR: 可读可写
        * O_NOCTTY: 该参数不会使打开的文件成为该进程的控制终端。如果没有指定这个标志，那么任何一个 输入都将会影响用户的进程。
        * O_SYNC: 等待物理 I/O 结束后再 write，包括更新文件属性的 I/O
    */
    string name = file_name_ + to_string(num);
    num = (num+1)%10;
    fd = open(name.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);     // 打开串口

//    std::cout<<"name："<<fd<<std::endl;

    if (fd == -1)
    {//串口打开失败
//        printf("open_port wait to open %s... \n",  file_name_);
        return false;
    }
    else
    {
        // fcntl函数是linux下的一个文件锁函数，用以加密文件，给文件上锁，防止文件同时被多个进程操作。
        fcntl(fd, F_SETFL, 0);
        printf("port is open %s... \n", file_name_);
    }

    // 提供了一个常规的终端接口，用于控制非同步通信端口
    struct termios port_settings;
    // B115200 115200波特
    cfsetispeed(&port_settings, B115200);   // 设置输入波特率
    cfsetospeed(&port_settings, B115200);   // 设置输出波特率

    /*
        * c_iflag：输入模式标志，控制终端输入方式
        * c_oflag：输出模式标志，控制终端输出方式
        * c_cflag：控制模式标志，指定终端硬件控制信息
        * c_lflag：本地模式标志，控制终端编辑功能
    */

    /*
        * 设置数据位
        * & ~CSIZE     把数据位清零
        * | CS8        把数据位设置为8位
    */
    //设置数据位
    port_settings.c_cflag = (port_settings.c_cflag & ~CSIZE) | CS8;//设置数据位为8位

    // ~IGNBRK       禁用忽略BREAK键输入（对不匹配的速度测试禁用IGNBRK，否则收到破坏）
    port_settings.c_iflag &= ~IGNBRK;         // 禁止中断处理
    port_settings.c_lflag = 0;                // 设置为零，表示没有信号字符，没有回音
    // 无规范处理
    port_settings.c_oflag = 0;                // 设置为零，表示没有重新映射，没有延迟
    port_settings.c_cc[VMIN] = 0;             // 最小字符，设置为零，表示读取不会被阻止
    port_settings.c_cc[VTIME] = 5;            // 等待时间，设置为五，表示0.5秒读取超时
    /*
        * ~IXON     禁止允许输入时对XON流进行控制
        * ~XOFF     禁止允许输入时对XOFF流进行控制
        * ~IXANY    禁止输入任何字符将重启停止的输出
    */
    port_settings.c_iflag &= ~(IXON | IXOFF | IXANY);
    /*
        * 通过位掩码的方式激活本地连接和接受使能选项
        * CLOCAL    略调制解调器线路状态（打开本地连接模式）
        * CREAD     使用接收器（开启串行数据接收）
    */
    port_settings.c_cflag |= (CLOCAL | CREAD);
    /*
        * 设置校验位
        * ~PARENB   禁止使用奇偶校验
        * ~PARODD   禁止对输入使用奇偶校验，禁止对输出使用偶校验
    */
    port_settings.c_cflag &= ~(PARENB | PARODD);        // 关闭奇偶校验

    port_settings.c_cflag |= 0;
    // 设置一位停止位
    // 一位停止位 &= ~CSTOPB            两位停止位 |= CSTOPB;
    port_settings.c_cflag &= ~CSTOPB;
    // 禁止使用RTS/CTS流控制
    port_settings.c_cflag &= ~CRTSCTS;
    port_settings.c_iflag = ICANON;
    port_settings.c_cc[VMIN] = 10;           // 最小字符，设置为10，表示读取被阻止10个字节
    port_settings.c_cc[VTIME] = 5;           // 等待时间，设置为五，表示0.5秒读取超时

    /*
        * 参数1: fd为打开的终端文件描述符
        * 参数2: optional_actions用于控制修改起作用的时间
        *        TCSANOW：不等数据传输完毕就立即改变属性
        *        TCSADRAIN：等待所有数据传输结束才改变属性
        *        TCSAFLUSH：等待所有数据传输结束,清空输入输出缓冲区才改变属性
        * 参数3: 结构体termios_p中保存了要修改的参数
    */
    tcsetattr(fd, TCSANOW, &port_settings);             // 将设置应用到串口
    return true;
}
// 发送数据
void SerialPort::send_data(uint8_t a[])
{
    int in_ = write(fd, a, write_dataLen);//发送数据
    if (in_ != write_dataLen)
    {
        cout << "!!! send data failure !!!\t:" << fd << endl;
        restart_serial();       // 如果串口发送失败，则考虑重新启动串口
        cout << "restart fd" << fd << endl;
    }
//    else
//        cout << "串口数据发送成功" <<fd<< endl;
}

// 接收数据
uint8_t* SerialPort::read_data()
{
    /*
        * tcflush() 刷新（扔掉）输入缓存或输出缓存
        * TCIFLUSH  刷新输入队列
        * TCOFLUSH  刷新输出队列
        * TCIOFLUSH 刷新输入，输出队列
    */

//    std::cout<<tcflush(fd, TCIFLUSH)<<std::endl;      // 丢弃输入缓冲区中的旧数据
    uint8_t* read_buffer = new uint8_t [Read_dataLen];       // 缓冲区存储接收到的数据
    int  bytes_read = 0;        // 存储系统调用read()所读取的字节数
//    std::cout<<"等待你发的值\t"<<Read_dataLen<<std::endl;
    //获取长度
//    cout << read_buffer<<"\t"<<fd << endl;
    bytes_read = read(fd, read_buffer, Read_dataLen);
//    std::cout<<"获取成功"<<std::endl;
//     读取数据
    if (bytes_read == -1 || bytes_read == 0)    // 读取失败
    {
        cout << "\t串口读取失败\t" << endl;
        restart_serial();// 重启串口
        return 0;
    }
    for(int i = 0;i<Read_dataLen;i++){
        std::cout<<int(read_buffer[i])<<"\t";
    }std::cout<<std::endl;
//    else
    //cout << "串口读取成功" << endl;
    return read_buffer;
}

// 重启串口
void SerialPort::restart_serial()
{
    close_port();//关闭当前串口，随后重新开启

    while(!OpenSerialPort());//重启
}

void SerialPort::close_port() {
    close(fd);
}