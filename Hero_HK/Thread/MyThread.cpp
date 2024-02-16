#include "MyThread.h"

ArmorDetect detect;
//读视频
void ReVideo()
{
    MyThread myThread;
    thread*Re_thread=new thread(bind(&MyThread::VideoThread,&myThread));
    thread*Os_thread=new thread(bind(&MyThread::decThread,&myThread));

    Re_thread->join();
    Os_thread->join();
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

        Mat processedFrame=frame.clone();
        imshow("processedFrame",frame);
        float fps=Videocapture.get(CAP_PROP_FPS);
        waitKey(1000/fps);

        lockGuard.unlock();//解锁
        DetectCondition.notify_all(); //检测条件不用等待了


    }
    Videocapture.release();//释放视频
    destroyAllWindows();//销毁所有窗口
    exit(0);
}

//识别线程
//在识别线程中，当图像为空时，线程调用DetectCondition进入等待状态，释放对mutexLock的持有锁。
//目的是为了让 视频/相机 线程有机会读入新的图像帧数并处理
//当 视频/相机 线程读到新的图像帧数后，先解锁，Condition进入等待状态，DetectCondition不用再等待了，进行检测操作
//再重复以上操作
void MyThread::decThread()
{

    while(1)
    {

        unique_lock<mutex> lockGuard(mutexLock);//加锁
        while(frame.empty())//如果图像为空，检测等待
        {
            DetectCondition.wait(lockGuard);
        }

        detect.run(frame);
        frame.release();
        Condition.notify_all();
        lockGuard.unlock();//解锁


    }
}


