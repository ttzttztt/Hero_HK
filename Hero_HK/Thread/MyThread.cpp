#include "MyThread.h"

//初始化线程：用来打开串口、PNP解算的初始化
MyThread::MyThread()
{
    cout<<"wait openSerialPort"<<endl;
    while(!serialPort.OpenSerialPort()); //开启串口
    cout<<"wait openCamera"<<endl;

    cout<<"over"<<endl;

}


//读视频
void ReVideo(Color &enemy_Color)
{
    MyThread myThread;
    //得到击打目标颜色
    myThread.enemy_Color=enemy_Color;

    thread*Re_thread=new thread(bind(&MyThread::VideoThread,&myThread));
    thread*Os_thread=new thread(bind(&MyThread::decThread,&myThread));
    thread*RePort_thread=new thread(bind(&MyThread::ReceivePortThread,&myThread));
    thread*SePort_thread=new thread(bind(&MyThread::SendPortThread,&myThread));


    Re_thread->join();
    Os_thread->join();
    RePort_thread->join();
    SePort_thread->join();

}

//读视频线程
void MyThread::VideoThread()
{

    VideoCapture Videocapture;
    string path="/home/tcrnx/Videos/Armor3.mp4";
    Videocapture.open(path);
    if(!Videocapture.isOpened())
    {
        cout<<"Failed to open video file "<<endl;
       exit(1);
    }

    while(true)
    {
        unique_lock<mutex> lockGuard(mutexLock);//加锁
        while(!frame.empty())
        {
            Condition.wait(lockGuard); //进入等待状态
        }

        if(!Videocapture.read(frame))//读取视频下一帧图像，如果无法取到，则break跳出
        {
            break;
        }

        //imshow("frame",frame);
        float fps=Videocapture.get(CAP_PROP_FPS);
        waitKey(1000/fps);
        waitKey(1);

        lockGuard.unlock();//解锁
        DetectCondition.notify_all(); //检测条件不用等待了


    }
    Videocapture.release();//释放视频
    destroyAllWindows();//销毁所有窗口
    exit(0);
}

//读相机
void ReCamera(Color &enemy_Color)
{
    MyThread myThread;
    //得到击打目标颜色
    myThread.enemy_Color=enemy_Color;

    thread*Re_thread=new thread(bind(&MyThread::CamerThread,&myThread));
    thread*Os_thread=new thread(bind(&MyThread::decThread,&myThread));
    thread*RePort_thread=new thread(bind(&MyThread::ReceivePortThread,&myThread));
    thread*SePort_thread=new thread(bind(&MyThread::SendPortThread,&myThread));


    Re_thread->join();
    Os_thread->join();
    RePort_thread->join();
    SePort_thread->join();
}


//相机读取线程
void MyThread::CamerThread()
{
    HaiKang.StartDevice(0);
    // 设置分辨率
    HaiKang.SetResolution(1280, 768);
    // 开始采集帧
    HaiKang.SetStreamOn();
    // 设置曝光事件
    HaiKang.SetExposureTime(60000);
    //HaiKang.SetGAIN(3,2);
    HaiKang.SetInfo();

    /* FPS
     * 初始化帧计数器fps_count 和帧率fps
     * 创建计时器start_time，end_time
     */
    double fps_count=0;
    fps=0;
    std::chrono::steady_clock::time_point start_time,end_time;
    //开始计时
    start_time=std::chrono::steady_clock::now();

    while(isContinue)
    {
        fps_count++;
        unique_lock<mutex> lockGuard(mutexLock);//加锁
        while(!frame.empty())
        {
            Condition.wait(lockGuard);//相机等待
        }
        if(!HaiKang.GetMat(frame))
        {
            //说明要重启
            cout<<"重启"<<endl;
            HaiKang.Reconnect();
        }
        if(waitKey(1)==27)
            isContinue=false;
        lockGuard.unlock();//  解锁
        DetectCondition.notify_all();//告知检测条件不用等待了


        end_time=std::chrono::steady_clock::now();
        //计算经过的时间
        double elapsed_time=std::chrono::duration_cast<std::chrono::duration<double>>(end_time-start_time).count();
        //如果经过的时间超过了设定的时间间隔 设定的间隔为1秒
        if(elapsed_time>=1)
        {
            fps=fps_count/elapsed_time;
            //重新设置计时器和帧计时器
            fps_count=0;
            start_time=end_time;
        }

    }
    frame.release();
    destroyAllWindows();//销毁所有窗口
}



//识别线程
//在识别线程中，当图像为空时，线程调用DetectCondition进入等待状态，释放对mutexLock的持有锁。
//目的是为了让 视频/相机 线程有机会读入新的图像帧数并处理
//当 视频/相机 线程读到新的图像帧数后，先解锁，Condition进入等待状态，DetectCondition不用再等待了，进行检测操作
//再重复以上操作
void MyThread::decThread()
{
    //图像初始化
    showImg=Mat::zeros(frame.size(),CV_8UC1);

    //载入SVM模型
    detect.loadSVM();
    //载入相机内参
    angleSolver.setData();
    angleSolver.setBulletSpeed(15000);


    while(isContinue)
    {

        unique_lock<mutex> lockGuard(mutexLock);//加锁
        while(frame.empty())//如果图像为空，检测等待
        {
            DetectCondition.wait(lockGuard);
        }

        detect.run(frame,enemy_Color);
        frame.copyTo(showImg);
        //给角度解算传目标装甲板值的实例
        double yaw=0,pitch=0,distance=0;
        //如果找到装甲板，就进行角度解算
        if(detect.state==ARMOR_FOUND)
        {
            angleSolver.getAngle(detect.targetArmor.armorVertices,detect.targetArmor.center,detect.targetArmor.type,yaw,pitch,distance);
            //绘制装甲板
            for (size_t i = 0; i < 4; i++)
            {
                line(showImg, detect.targetArmor.armorVertices[i], detect.targetArmor.armorVertices[(i + 1) % 4], Scalar(255, 255, 255), 2, 8, 0);
            }
            putText(showImg, fmt::format("pit={}", round(pitch)), {10, 65}, cv::FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));
            putText(showImg, fmt::format("yaw={}", round(yaw)), {10, 85}, cv::FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));
            putText(showImg, fmt::format("dis={}", int(distance)), {10, 105}, cv::FONT_HERSHEY_SIMPLEX, 1,Scalar(255, 255, 255));
            putText(showImg, fmt::format("type={}", detect.targetArmor.type), {10, 125}, cv::FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));

        }
        else
        {
            //serialPort.Data(yaw,pitch,distance,detect.targetArmor.armorNum);


        }
        //屏幕显示帧率
        putText(showImg, fmt::format("fps={}",int(fps)), {10, 45}, cv::FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255));

        imshow("showImg",showImg);


        frame.release();
        Condition.notify_all();
        lockGuard.unlock();//解锁

    }
}

//串口发送线程
void MyThread::SendPortThread()
{

    while(isContinue)//时刻接受数据
    {
//        sleep(1);
        float y=angleSolver.yaw();
        float p=angleSolver.pitch();
        double dis=angleSolver.dist();
        serialPort.send_data(analyzeData.TransData(p,y,dis));
        analyzeData.isSend=false;
    }
    exit(1);
}


//串口接收线程
void MyThread::ReceivePortThread()
{
    while(isContinue)//时刻接收数据
    {
        //数据接受，并且进行分析
        analyzeData.setData(serialPort.read_data());
        //得到击打目标颜色
        enemy_Color=analyzeData.getcolor();
        analyzeData.SetPortIsOpen();

    }
}















