#ifndef __POINTS_HPP__
#define __POINTS_HPP__

#include <iostream>
/*
 * 坐标类
 */

class Points
{

public:
    // 构造函数，初始化x和y坐标
    Points(int x, int y);
    // 析构函数
    ~Points();

    // 比较坐标
    bool operator==(const Points &p);

    // 获取x坐标
    int x() const;
    // 获取y坐标
    int y() const;

    // 设置x坐标
    void setX(int x);
    // 设置y坐标
    void setY(int y);

private:
    int ts_x; /* x坐标 */
    int ts_y; /* y坐标 */
};

#endif