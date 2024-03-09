#include"Analaze_Data.h"

float u8Arry2float(uint8_t *data)
{
    float fa = 0;
    uint8_t uc[4];
    uc[0] = data[0];
    uc[1] = data[1];
    uc[2] = data[2];
    uc[3] = data[3];

    memcpy(&fa, uc, 4);
    return fa;
}

void float2u8Arry(uint8_t *u8Arry, float *floatdata)
{
    uint8_t farray[4];
    *(float *)farray = *floatdata;
    u8Arry[0] = farray[0];
    u8Arry[1] = farray[1];
    u8Arry[2] = farray[2];
    u8Arry[3] = farray[3];

}


//发送数据封装
uint8_t * Analyze_Data::TransData(float myPitch,float myYaw,double dis)
{

    uint8_t* data = new uint8_t[write_dataLen];
    float p = myPitch, y = myYaw; //myYaw
    float l = dis;//距离

    data[0]=0x70;//设置数据
    float2u8Arry(&data[1],&y);
    float2u8Arry(&data[5],&p);
    data[9] = int(l/100);
    data[10] = int(l)%100;
    data[11] = PortIsOpen;
    data[write_dataLen-1]=0x6F;

//    for(int i=0;i<write_dataLen;i++)
//    {
//        std::cout<<int(data[i])<<'\t';
//    }std::cout<<std::endl;
    return data;
}

//分析数据
void Analyze_Data::setData(uint8_t* c)
{
    if(c == 0)
        return;
    int i =0;
    for(;i<Read_dataLen-13 + 1;i++)
    {
        if(int(c[i])==128 && int(c[i+(Read_dataLen/2)-1])==127)
        {
            break;
        }
    }
    if(i>= Read_dataLen/2)
        return;

    //输出接收信息
//    for(int j = i;j<13 + i;j++)
//    {
//        std::cout<<int(c[j])<<'\t';
//    }std::cout<<std::endl;

    color = int(c[i+1]);//判断需要检测的图片类型
    V = int(c[i+2])*1.0/10 ;//速度

    SPit = u8Arry2float(&c[i+3]);
    SYaw = u8Arry2float(&c[i+7]);

    int temp = int(c[i+11]); // 百位 1正常 2哨兵 十位 1 普通自瞄   2 预测 个位 1 15/s 2 30/s
    speedmodel = temp%10;//速度模式
    auto_aim_state = temp/10%10;//预测模式
    model = temp/100;//是否开启哨兵模式
}

//返回击打目标颜色
Color Analyze_Data::getcolor()
{
    if(color==0)
        return BLUE;
    else if(color==1)
        return RED;
}

//判断串口是否正确打开
void Analyze_Data::SetPortIsOpen()
{
    if(PortIsOpen!=2)//判断是否等于2 不是则等于2
        PortIsOpen = 2;//说明串口正确打开
}

