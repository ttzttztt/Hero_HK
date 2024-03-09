#include "Thread/MyThread.h"


enum ModelType {
    Pic = 1, Vid = 2, Car = 3
};//模式
int debug_level = 2;//bug等级

int main() {
    ModelType type = Car;//定义类型
    Color enemy_Color = RED;//0 blue    1 red
    switch (type) {
        case 1: {
            //RePicture(enemy_Color);//读图片
            break;
        }
        case 2: {
            ReVideo(enemy_Color);//读视频
            break;
        }
        case 3: {

            ReCamera(enemy_Color);//读相机
            break;
        }
    }

    return 0;
}