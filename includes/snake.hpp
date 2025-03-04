#ifndef __SNAKE_HPP__
#define __SNAKE_HPP__

#include <vector>
#include <iostream>

#include "apple.hpp"

// 定义一个表示方向的枚举
enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Position
{
public:
    int x;
    int y;
    // 默认构造函数
    Position() : x(0), y(0) {}
    Position(int x, int y) : x(x), y(y) {}
};

class Snake
{
private:
    // 蛇身各节的坐标
    std::vector<Position> body;
    // 蛇的移动方向
    Direction direction;
    // 蛇的移动速度
    int speed;
    // 新增：表示蛇是否暂停
    bool isPausedstate;

public:
    // 构造函数，初始化蛇的位置和节数
    Snake(int initialX, int initialY, int initialLength, Direction initialDirection, int initialSpeed = 1);

    // 设置蛇的速度
    void setSpeed(int newSpeed);

    // 获取蛇的速度
    int getSpeed() const;

    // 设置蛇的方向
    void setDirection(Direction newDirection);

    // 移动蛇的方法
    void move();

    // 让蛇增长的方法
    void grow();

    // 检查蛇是否撞到自己或边界
    bool isCollision(int &x, int &y);

    // 获取蛇身节数
    int getLength() const;

    // 获取蛇的整体位置
    const std::vector<Position> &getBody() const;

    // 获取蛇的头部位置
    const Position &getHead() const;

    // 重置蛇的状态
    void reset(int initialX, int initialY, int initialLength, Direction initialDirection, int initialSpeed);

    void setStatus(int status);

    // 判断蛇是否处于暂停状态
    bool isPaused() const;
};

#endif // __SNAKE_HPP__