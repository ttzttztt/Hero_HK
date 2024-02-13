#include "MyThread.h"


//读视频
void ReVideo()
{
    MyThread myThread;
    thread*Re_thread=new thread(bind(&MyThread::VideoThread,&myThread));
    Re_thread->join();
}

//读视频线程
void MyThread::VideoThread()
{
    VideoCapture Videocapture;
    string path="/home/tcrnx/Videos/Armor1.mp4";
    Videocapture.open(path);
    if(!Videocapture.isOpened())
    {
        cout<<"Failed to open video file "<<endl;
       exit(1);
    }

    while(isContinue)
    {
        unique_lock<mutex> lockGuard(mutexLock);//所锁
        if(!Videocapture.read(frame))//读取视频下一帧图像，如果无法取到，则break跳出
        {
            break;
        }
        imshow("frame",frame);
        float fps=Videocapture.get(CAP_PROP_FPS);
        waitKey(1000/fps);

        if(waitKey(1)==27)
        {
            isContinue=false;
        }
        lockGuard.unlock();//解锁
    }
    Videocapture.release();//释放视频
    destroyAllWindows();//销毁所有窗口
    exit(0);
}


