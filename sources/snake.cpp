#include "../includes/snake.hpp"
#include "../includes/points.hpp"
#include "../includes/bmp.hpp"
#include <iostream>
#include <unistd.h> // 用于 sleep 函数

// 构造函数实现
Snake::Snake(int initialX, int initialY, int initialLength, Direction initialDirection, int initialSpeed)
    : direction(initialDirection), speed(initialSpeed), isPausedstate(false)
{
    // 显示网格
    LCD *lcd = LCD::getInstance();
    int *mp = lcd->lcdaddr();
    BMP *grid = new BMP("./img/grid.bmp");
    delete grid;

    // 初始化蛇身，初始位置为 (initialX, initialY)，尾部向左延伸
    for (int i = 0; i < initialLength; ++i)
    {
        body.push_back(Position(initialX - i, initialY));
        // 在lcd上绘制蛇身
        BMP *snake = new BMP("./img/snake.bmp");
        snake->show(mp, initialX - i, initialY); // 显示蛇身
        delete snake;                            // 释放内存
    }
}

// 设置速度
void Snake::setSpeed(int newSpeed)
{
    speed = newSpeed;
}

// 获取速度
int Snake::getSpeed() const
{
    return speed;
}

// 设置方向
void Snake::setDirection(Direction newDirection)
{
    direction = newDirection;
}

// 移动蛇
void Snake::move()
{
    if (isPausedstate)
    {
        return; // 如果暂停，则不进行移动操作
    }

    // 根据方向更新蛇的头部位置
    Position newHead = body.front();
    switch (direction)
    {
    case Direction::UP:
        newHead.y -= speed;
        break;
    case Direction::DOWN:
        newHead.y += speed;
        break;
    case Direction::LEFT:
        newHead.x -= speed;
        break;
    case Direction::RIGHT:
        newHead.x += speed;
        break;
    }

    // 移除蛇尾
    Position tail = body.back();
    body.pop_back();

    // 添加新的头部
    body.insert(body.begin(), newHead);

    // 刷新蛇身位置，通过刷图片实现
    LCD *lcd = LCD::getInstance();
    int *mp = lcd->lcdaddr();
    BMP *snake = new BMP("./img/snake.bmp");
    BMP *grid = new BMP("./img/grid.bmp");

    // 清除原来的蛇尾，通过刷新网格到蛇尾的位置
    grid->show(mp, tail.x, tail.y);

    // 显示新的蛇身
    for (const auto &pos : body)
    {
        snake->show(mp, pos.x, pos.y);
    }

    delete snake;
    delete grid;

    // 每秒进行一次移动
    usleep(1000000 / speed);
}

// 让蛇增长
void Snake::grow()
{
    if (isPausedstate)
    {
        return; // 如果暂停，则不进行增长操作
    }

    // 添加一节蛇身到尾部
    Position tail = body.back();
    Position newTail;
    switch (direction)
    {
    case Direction::UP:
        newTail = Position(tail.x, tail.y + speed);
        break;
    case Direction::DOWN:
        newTail = Position(tail.x, tail.y - speed);
        break;
    case Direction::LEFT:
        newTail = Position(tail.x + speed, tail.y);
        break;
    case Direction::RIGHT:
        newTail = Position(tail.x - speed, tail.y);
        break;
    }
    body.push_back(newTail);

    // 在lcd上绘制新增的蛇身
    LCD *lcd = LCD::getInstance();
    int *mp = lcd->lcdaddr();
    BMP *snake = new BMP("./img/snake.bmp");
    snake->show(mp, newTail.x, newTail.y);
    delete snake;
}

// 检查是否碰撞
bool Snake::isCollision(int &x, int &y)
{
    if (isPausedstate)
    {
        return false; // 如果暂停，不进行碰撞检测
    }

    // 检测是否撞到边界
    const int minX = 13;
    const int maxX = 790;
    const int minY = 113;
    const int maxY = 430;
    Position head = body.front();
    if (head.x < minX || head.x >= maxX || head.y < minY || head.y >= maxY)
    {
        return true;
    }

    // 检测是否撞到自己
    for (auto it = body.begin() + 1; it != body.end(); ++it)
    {
        if (it->x == head.x && it->y == head.y)
        {
            return true;
        }
    }

    // 检测是否吃到食物
    if (head.x == x && head.y == y)
    {
        return false;
    }

    return false;
}

// 重置蛇的状态
void Snake::reset(int initialX, int initialY, int initialLength, Direction initialDirection, int initialSpeed)
{
    // 清除当前蛇身
    LCD *lcd = LCD::getInstance();
    int *mp = lcd->lcdaddr();
    BMP *grid = new BMP("./img/grid.bmp");
    for (const auto &pos : body)
    {
        grid->show(mp, pos.x, pos.y);
    }
    delete grid;

    // 清空蛇身向量
    body.clear();

    // 重新初始化蛇的状态
    direction = initialDirection;
    speed = initialSpeed;
    isPausedstate = false;

    // 重新初始化蛇身，初始位置为 (initialX, initialY)，尾部向左延伸
    for (int i = 0; i < initialLength; ++i)
    {
        body.push_back(Position(initialX - i, initialY));
        // 在lcd上绘制蛇身
        BMP *snake = new BMP("./img/snake.bmp");
        snake->show(mp, initialX - i, initialY); // 显示蛇身
        delete snake;                            // 释放内存
    }
}

// 获取蛇身节数
int Snake::getLength() const
{
    return body.size();
}

// 获取蛇的整体位置
const std::vector<Position> &Snake::getBody() const
{
    return body;
}

// 获取蛇的头部位置
const Position &Snake::getHead() const
{
    return body.front();
}

// 根据 int 类型的状态值设置蛇的暂停或恢复状态
void Snake::setStatus(int status)
{
    isPausedstate = (status != 0);
}

// 获取蛇的暂停状态
bool Snake::isPaused() const
{
    return isPausedstate;
}