#include "HaikangCameraRGB.h"



HaiKangCameraRGB::~HaiKangCameraRGB()
{
    nRet = MV_CC_FreeImageBuffer(handle, (&pFrame));
    if(nRet == MV_OK)
    {
        fmt::print(fmt::fg(fmt::color::blue), "[CameraRGB] free image buffer succeed!\n");
    }
    else
    {
        fmt::print(fmt::fg(fmt::color::red), "[CameraRGB] free image buffer failed!\n");
    }
}

int HaiKangCameraRGB::StartDevice(int serial_number)
{
    //打开设备
    MV_CC_DEVICE_INFO_LIST stDeviceList;
    memset(&stDeviceList, 0, sizeof(MV_CC_DEVICE_INFO_LIST));

    //枚举设备
    nRet = MV_CC_EnumDevices(MV_USB_DEVICE, &stDeviceList);
//    printf("res:%x\n",nRet);
    if(MV_OK != nRet)
    {
//        fmt::print(fmt::fg(fmt::color::red), "EnumDevices failed! nRet [%x]\n", nRet);
        return -1;
    }

    if(stDeviceList.nDeviceNum > 0) //设备数量不为0
    {
//         for(int i = 0; i < stDeviceList.nDeviceNum; i++)
//         {
//             printf("[device %d]:\n", i);
//             MV_CC_DEVICE_INFO* pDeviceInfo = stDeviceList.pDeviceInfo[i];
//             if(NULL == pDeviceInfo)
//             {
//                 printf("pDeviceInfo is NULL!\n");
//                 return -1;
//             }
//             HaiKangCamera::PrintDeviceInfo(pDeviceInfo);
//         }

        //打开设备
        //选择设备并创建句柄
        nRet = MV_CC_CreateHandle(&handle, stDeviceList.pDeviceInfo[serial_number]);
        if(MV_OK != nRet)
        {
            fmt::print(fmt::fg(fmt::color::red), "CreateHandle failed! nRet [%x]\n", nRet);
            return -1;
        }

        //打开设备
        nRet = MV_CC_OpenDevice(handle);
        if(MV_OK == nRet)
        {
            fmt::print(fmt::fg(fmt::color::blue), "[CameraRGB] open succeed!\n");
            return serial_number;
        }
        if(MV_OK != nRet)
        {
            fmt::print(fmt::fg(fmt::color::red), "[CameraRGB] open failed!\n");
            return -1;
        }
    }
    else
    {
        fmt::print(fmt::fg(fmt::color::red), "[CameraRGB] Find No Devices!\n");
        return -1;
    }

    return serial_number;
}

bool HaiKangCameraRGB::SetStreamOn()
{   //开始采集
    //设置触发模式为off
    this->nRet = MV_CC_SetEnumValue(handle, "TriggerMode", 0);
    if(MV_OK != nRet)
    {
        fmt::print(fmt::fg(fmt::color::red), "[CameraRGB] SetEnumValue failed! nRet [%x]!\n", nRet);
        return false;
    }

    //设置采集模式为连续采集
    this->nRet = MV_CC_SetEnumValue(handle, "AcquisitionMode", 2);
    if(MV_OK != nRet)
    {
        fmt::print(fmt::fg(fmt::color::red), "[CameraRGB] SetEnumValue failed! nRet [%x]!\n", nRet);
        return false;
    }

    // //获取数据包大小
    // MVCC_INTVALUE stParam;
    // memset(&stParam, 0, sizeof(MVCC_INTVALUE));
    // nRet = MV_CC_GetIntValue(handle, "PayloadSize", &stParam);
    // if (MV_OK != nRet)
    // {
    //     printf("Get PayloadSize fail! nRet [0x%x]\n", nRet);
    //     return false;
    // }
    // g_nPayloadSize = stParam.nCurValue;

    //开始取流
    nRet = MV_CC_StartGrabbing(handle);
    if(MV_OK == nRet)
    {
        fmt::print(fmt::fg(fmt::color::blue), "[CameraRGB] StartGrabbing succeed!\n");
        return true;
    }
    else
    {
        fmt::print(fmt::fg(fmt::color::red), "[CameraRGB] StartGrabbing failed! nRet [%x]\n", nRet);
        return false;
    }

    //创建相机图像采集线程
    // pthread_t tid;
    // nRet = pthread_create(&tid, NULL, HaiKangCamera::WorkThread, handle);
    // if(MV_OK == nRet)
    // {
    //     printf("pthread_create succeed!\n");
    //     return true;
    // }
    // else
    // {
    //     printf("pthread_create failed! nRet [%d]\n", nRet);
    //     return false;
    // }
}

bool HaiKangCameraRGB::SetResolution(int width, int height)
{   //TODO:分辨率根据相机采集上限设置，目前设置为1280*1024
    nRet = MV_OK;

    //设置像素格式
    nRet = MV_CC_SetPixelFormat(handle, PixelType_Gvsp_BGR8_Packed);

    if(nRet != MV_OK)
    {
        fmt::print(fmt::fg(fmt::color::red), "[CameraRGB] setPixelFormat failed! nRet [%x]\n", nRet);
        return false;
    }

    nRet = MV_CC_SetIntValue(this->handle, "Width", width);
    if(nRet != MV_OK)
    {
        fmt::print(fmt::fg(fmt::color::red), "[CameraRGB] setResolution failed! nRet [%x]\n", nRet);
        return false;
    }
    nRet = MV_CC_SetIntValue(this->handle, "Height", height);
    if(nRet != MV_OK)
    {
        fmt::print(fmt::fg(fmt::color::red), "[CameraRGB] setResolution failed! nRet [%x]\n", nRet);
        return false;
    }
    nRet = MV_CC_SetIntValue(this->handle, "OffsetX", 80);//偏移量X
    if(nRet != MV_OK)
    {
        fmt::print(fmt::fg(fmt::color::red), "[CameraRGB] setResolution failed! nRet [%x]\n", nRet);
        return false;
    }
    nRet = MV_CC_SetIntValue(this->handle, "OffsetY", 0);//偏移量Y

    if(nRet == MV_OK)
    {
        fmt::print(fmt::fg(fmt::color::blue), "[CameraRGB] setResolution succeed! nRet [%x]\n", nRet);
        return true;
    }
    else
    {
        printf("setResolution failed!\n");
        fmt::print(fmt::fg(fmt::color::red), "[CameraRGB] setResolution failed! nRet [%x]\n", nRet);
        return false;
    }


}

bool HaiKangCameraRGB::SetExposureTime(float ExposureTime)
{   //设置曝光时间
    nRet = MV_CC_SetFloatValue(this->handle, "ExposureTime", ExposureTime);
    if(nRet == MV_OK)
    {
        fmt::print(fmt::fg(fmt::color::green), "[CAMERA] 曝光值设置成功\n");
        return true;
    }
    else
    {
        fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 曝光值设置失败\n");
        return false;
    }
}

bool HaiKangCameraRGB::SetGAIN(int value, int ExpGain)
{   //曝光增益
    if(value == 0)
    {
        nRet = MV_CC_SetEnumValue(handle, "GainMode", R_CHANNEL);
    }
    else if(value == 1)
    {
        nRet = MV_CC_SetEnumValue(handle, "GainMode", G_CHANNEL);
    }
    else if(value == 2)
    {
        nRet = MV_CC_SetEnumValue(handle, "GainMode", B_CHANNEL);
    }
    else
    {
        nRet = MV_CC_SetFloatValue(handle, "Gain", ExpGain);
        if(nRet == MV_OK)
        {
            fmt::print(fmt::fg(fmt::color::blue), "[CAMERA] 设置曝光增益成功！\n");
            return true;
        }
        else
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 设置曝光增益失败！\n");
            return false;
        }
    }

    nRet = MV_CC_SetFloatValue(handle, "Gain", ExpGain);
    if(nRet == MV_OK)
    {
        fmt::print(fmt::fg(fmt::color::blue), "[CAMERA] 设置曝光增益成功！\n");
        return true;
    }
    else
    {
        fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 设置曝光增益失败！\n");
        return false;
    }
}

bool HaiKangCameraRGB::Set_Auto_BALANCE()
{   //自动白平衡（具有记忆功能）
    this->nRet = MV_CC_SetEnumValue(this->handle, "BalanceWhiteAuto", 1);
    if(nRet != MV_OK)
    {
        fmt::print(fmt::fg(fmt::color::blue), "[CAMERA] 自动白平衡设置失败！\n");
        return false;
    }
    else
    {
        fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 自动白平衡设置成功！\n");
        return true;
    }
}

bool HaiKangCameraRGB::Set_BALANCE(int value, unsigned int value_number)
{   //手动白平衡（具有记忆功能））
    //关闭自动白平衡
    this->nRet = MV_CC_SetEnumValue(handle, "BalanceWhiteAuto", MV_BALANCEWHITE_AUTO_OFF);
    if(nRet != MV_OK)
    {
        fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 关闭自动白平衡失败！\n");
        return false;
    }

    //设置RGB三通道白平衡值
    if(value == 0)
    {
        this->nRet = MV_CC_SetBalanceRatioRed(handle, value_number);

        if(nRet == MV_OK)
        {
            fmt::print(fmt::fg(fmt::color::blue), "[CAMERA] set R_Balance succeed！\n");
            return true;
        }
        else
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA] set R_Balance failed！\n");
            return false;
        }
    }
    else if(value == 1)
    {
        this->nRet = MV_CC_SetBalanceRatioGreen(handle, value_number);

        if(nRet == MV_OK)
        {
            fmt::print(fmt::fg(fmt::color::blue), "[CAMERA] set G_Balance succeed！\n");
        }
        else
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA] set G_Balance failed！\n");
            return false;
        }
    }
    else if(value == 2)

    {
        this->nRet = MV_CC_SetBalanceRatioBlue(handle, value_number);

        if(nRet == MV_OK)
        {
            fmt::print(fmt::fg(fmt::color::blue), "[CAMERA] set B_Balance succeed！\n");
        }
        else
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA] set B_Balance failed！\n");
            return false;
        }
    }
    return true;
}

bool HaiKangCameraRGB::Set_Gamma(bool set_status,double dGammaParam)
{   //设置Gamma值
    if(set_status == true)
    {
        nRet = MV_CC_SetEnumValue(handle, "Gamma", 1);
        if(nRet == MV_OK)
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 设置Gamma值成功！\n");
            return true;
        }
        else
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 设置Gamma值失败！\n");
            return false;
        }
    }
    else
    {
        nRet = MV_CC_SetEnumValue(handle, "Gamma", 0);
        if(nRet == MV_OK)
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 关闭Gamma值成功！\n");
            return true;
        }
        else
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 关闭Gamma值失败！\n");
            return false;
        }
    }
}

bool HaiKangCameraRGB::Color_Correct(bool value)
{   //设置色彩校正
    if(value == true)
    {
        nRet = MV_CC_SetEnumValue(handle, "ColorCorrection", 1);
        if(nRet == MV_OK)
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 设置色彩校正成功！\n");
            return true;
        }
        else
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA]设置色彩校正失败！\n");
            return false;
        }
    }
    else
    {
        nRet = MV_CC_SetEnumValue(handle, "ColorCorrection", 0);
        if(nRet == MV_OK)
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 关闭色彩校正成功！\n");
            return true;
        }
        else
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 关闭色彩校正失败！\n");
            return false;
        }
    }
}

bool HaiKangCameraRGB::Set_Contrast(bool set_status,int dContrastParam)
{   //设置对比度
    if(set_status == true)
    {
        nRet = MV_CC_SetEnumValue(handle, "Contrast", 1);
        if(nRet == MV_OK)
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 设置对比度成功！\n");
            return true;
        }
        else
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 设置对比度失败！\n");
            return false;
        }
    }
    else
    {
        nRet = MV_CC_SetEnumValue(handle, "Contrast", 0);
        if(nRet == MV_OK)
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 关闭对比度成功！\n");
            return true;
        }
        else
        {
            fmt::print(fmt::fg(fmt::color::red), "[CAMERA] 关闭对比度失败！\n");
            return false;
        }
    }
}

bool HaiKangCameraRGB::UpdateTimestampOffset(std::chrono::_V2::steady_clock::time_point time_start)
{   //计算时间戳偏移
    std::chrono::_V2::steady_clock::time_point time_end = std::chrono::_V2::steady_clock::now();
    std::chrono::duration<double> time_span = time_end - time_start;
    timestamp_offset = time_span.count() * 1000;
    return true;
}

int HaiKangCameraRGB::Get_TIMESTAMP()
{   //获取时间戳
    std::chrono::_V2::steady_clock::time_point time_start = std::chrono::_V2::steady_clock::now();
    return ((int)time_start.time_since_epoch().count() - timestamp_offset);
}

HaiKangCameraRGB::HaiKangCameraRGB()
{

}

bool HaiKangCameraRGB::GetMat(cv::Mat &Src)
{

    //从缓存区读取图像
    nRet = MV_CC_GetOneFrameTimeout(handle, pData, nDataSize, &stImageInfo, 1000);
    if (MV_OK != nRet)
    {
        std::cout<<"connect failed"<<std::endl;
        return false;
    }
    cv::Mat src = cv::Mat(stImageInfo.nHeight, stImageInfo.nWidth, CV_8UC3);
    memcpy(src.data, pData, stImageInfo.nWidth * stImageInfo.nHeight*3);
    if(src.empty()){
        std::cout<<"Camera Mat is empty"<<std::endl;
        return false;
    }
    resize(src, Src, Size(640,384), 0, 0, INTER_NEAREST);//修改尺寸
    //flip：0是绕x轴翻转（垂直翻转）
    //flip：1是绕y轴翻转（水平翻转）
    flip(Src,Src,1);

    return true;
}

bool HaiKangCameraRGB::SetInfo() {
    // ch:获取数据包大小 | en:Get payload size

    memset(&stParam, 0, sizeof(MVCC_INTVALUE));
    nRet = MV_CC_GetIntValue(handle, "PayloadSize", &stParam);
    if (MV_OK != nRet)
    {
        fmt::print(fmt::fg(fmt::color::red), "[CAMERA] Get PayloadSize fail! nRet [0x%x]\n", nRet);
        return false;
    }

    stImageInfo = {0};
    memset(&stImageInfo, 0, sizeof(MV_FRAME_OUT_INFO_EX));
    pData = (unsigned char *)malloc(sizeof(unsigned char) * stParam.nCurValue);
    if (NULL == pData)
    {
        return false;
    }
    nDataSize = stParam.nCurValue;
    return true;
}

bool HaiKangCameraRGB::Reconnect()
{
    nRet = MV_CC_StopGrabbing(handle);
    nRet = MV_CC_CloseDevice(handle);
    nRet = MV_CC_DestroyHandle(handle);
    handle = NULL;
    StartDevice(0);
    // 设置分辨率
    SetResolution(1280, 768);
    // 开始采集帧
    SetStreamOn();
    // 设置曝光事件
    SetExposureTime(20000);
//    SetGAIN(3,2);
    SetInfo();

}
