cmake_minimum_required(VERSION 3.24)
project(Hero_HK)

set(CMAKE_CXX_STANDARD 14)


find_package(OpenCV REQUIRED)
find_package(Sophus REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(fmt REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Sophus_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Fmt_INCLUDE_DIRS})

#多线程
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-pthread")


add_executable(Hero_HK
        main.cpp
        Thread/MyThread.cpp
        Thread/MyThread.h
        Armor/ArmorDetect.cpp
        Armor/ArmorDetect.h
        Struct.h
        Drawing.cpp
        Armor/LightBar.cpp
        Armor/ArmorBox.cpp
        Armor/NumClassifier.cpp
        PNP_Distance/PNP_Distance.cpp
        PNP_Distance/PNP_Distance.h
        Armor/matchArmors.cpp
        HaikangCamera/HaikangCameraRGB.cpp
        HaikangCamera/HaikangCameraRGB.h
        SerialPort/SerialPort.cpp
        SerialPort/SerialPort.h
        Analaze_Data/Analaze_Data.cpp Analaze_Data/Analaze_Data.h)

target_link_libraries(Hero_HK ${OpenCV_LIBS})
target_link_libraries(Hero_HK ${pthread})
target_link_libraries(Hero_HK ${Sophus})
target_link_libraries(Hero_HK ${Eigen3_LIBRARIES})

# 包含海康相机动态链接库
find_library(MVS_LIB libMvCameraControl.so /opt/MVS/lib/aarch64/)
target_link_libraries(Hero_HK ${MVS_LIB})
target_link_libraries(Hero_HK fmt::fmt)