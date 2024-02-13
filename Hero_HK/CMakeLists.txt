cmake_minimum_required(VERSION 3.24)
project(Hero_HK)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

#多线程
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-pthread")

add_executable(Hero_HK
        main.cpp
        Thread/MyThread.cpp
        Thread/MyThread.h)

target_link_libraries(Hero_HK ${OpenCV_LIBS})
target_link_libraries(Hero_HK ${pthread})