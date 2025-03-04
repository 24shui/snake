#include "../includes/points.hpp"
using namespace std;

// 构造函数，初始化Points类的成员变量ts_x和ts_y
Points::Points(int x, int y) : ts_x(x), ts_y(y)
{
}

// 析构函数，用于释放Points对象占用的内存
Points::~Points()
{
}

// 重载==运算符，判断两个Points对象是否相等
bool Points::operator==(const Points &p)
{
    // 如果两个对象的x坐标和y坐标相等，则返回true
    if (ts_x == p.ts_x && ts_y == p.ts_y)
    {
        return true;
    }
    // 否则返回false
    return false;
}

// 设置点的x坐标
void Points::setX(int x)
{
    // 将传入的x坐标赋值给成员变量ts_x
    ts_x = x;
}

// 设置点的y坐标
void Points::setY(int y)
{
    // 将传入的y坐标赋值给成员变量ts_y
    ts_y = y;
}

// 返回点的x坐标
int Points::x() const
{
    return ts_x;
}

// 返回点的y坐标
int Points::y() const
{
    return ts_y;
}
