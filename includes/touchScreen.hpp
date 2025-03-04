#ifndef __TOUCHSCREEN_HPP__
#define __TOUCHSCREEN_HPP__

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/input.h>
#include "points.hpp"
using namespace std;

#define TS_PATH "/dev/input/event0"
#define MIN_SWIPE_DISTANCE 50

// 定义手势类型的枚举
enum GestureType
{
    NONE,
    CLICK,
    SWIPE_UP,
    SWIPE_DOWN,
    SWIPE_LEFT,
    SWIPE_RIGHT
};

class TouchScreen
{
private:
    // 构造函数
    TouchScreen();

public:
    // 析构函数
    ~TouchScreen();

    // 创建实例
    static TouchScreen *instance();
    // 删除实例
    static void del_instance();

    // 获取触摸事件坐标，同时返回手势类型
    GestureType wait(Points &p);

    // 静态成员变量，保存实例指针
    static TouchScreen *m_instance;
    // 静态成员变量，保存文件描述符
    static int fd;
};

#endif