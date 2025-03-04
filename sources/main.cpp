#include "../includes/lcd.hpp"
#include "../includes/touchScreen.hpp"
#include "../includes/points.hpp"
#include "../includes/bmp.hpp"
#include "../includes/snake.hpp"
#include "../includes/apple.hpp"
#include "../includes/score.hpp"
#include "../includes/showfont.hpp"
#include <thread>

using namespace std;

int *mp;
GestureType direction;            // 方向
int apple_x, apple_y;             // 苹果坐标
int speed = 10;                   // 蛇移动速度
Points *point = new Points(0, 0); // 初始化坐标点
// 生成蛇
Snake snake(205, 270, 3, Direction::RIGHT, 1); // 初始化蛇
int status = 0;                                // 游戏状态

// 触摸屏线程函数
void touchScreenThread(TouchScreen *ts, Points *point)
{
    while (1)
    {
        direction = ts->wait(*point);
        {
            std::cout << "x: " << point->x() << " y: " << point->y() << std::endl;
        }

        if (status == 1)
        {
            // 退出游戏
            break;
        }
    }
}

void initGame(Snake *snake, Apple &apple, BMP *&appleImg, BMP *&grid)
{
    apple = Apple(13, 13, 13, 113, 790, 430);  // 生成食物
    appleImg = new BMP("./img/apple.bmp");     // 生成食物图片
    grid = new BMP("./img/grid.bmp");          // 生成网格图片
    apple.getRandomPosition(apple_x, apple_y); // 随机生成食物坐标
    appleImg->show(mp, apple_x, apple_y);      // 显示食物
    snake->setSpeed(10);
}

void snakeRunThread(Snake *snake, Score score)
{
    Apple apple(13, 13, 13, 113, 790, 430);     // 生成食物
    BMP *appleImg = new BMP("./img/apple.bmp"); // 生成食物图片
    BMP *grid = new BMP("./img/grid.bmp");      // 生成网格图片
    apple.getRandomPosition(apple_x, apple_y);  // 随机生成食物坐标
    appleImg->show(mp, apple_x, apple_y);       // 显示食物
    snake->setSpeed(10);
    snake->setStatus(false); // 开始游戏，恢复运动

    while (true)
    {
        bool isGamePaused = snake->isPaused();

        if (!isGamePaused)
        {
            score.displayScore(55, 55);                     // 显示分数
            system("madplay -a -3 ./bgm/retro-8bit.mp3 &"); // 播放背景音乐

            // 根据滑动方向设置蛇的移动方向
            switch (direction)
            {
            case SWIPE_RIGHT:

                snake->setDirection(Direction::RIGHT);
                break;
            case SWIPE_LEFT:

                snake->setDirection(Direction::LEFT);
                break;
            case SWIPE_UP:

                snake->setDirection(Direction::UP);
                break;
            case SWIPE_DOWN:

                snake->setDirection(Direction::DOWN);
                break;
            }

            snake->move(); // 移动蛇

            if (snake->isCollision(apple_x, apple_y)) // 碰撞到食物边界
            {
                std::cout << "Game over!" << std::endl;
                system("killall -9 madplay"); // 停止播放背景音乐
                break;
            }

            std::cout << apple_x << " " << apple_y << std::endl; // 打印食物坐标
            std::cout << "x: " << snake->getHead().x << " y: " << snake->getHead().y << std::endl;

            // 检查是否吃到食物
            if (snake->getHead().x >= apple_x && snake->getHead().x < apple_x + 23 &&
                snake->getHead().y >= apple_y && snake->getHead().y < apple_y + 23)
            {
                score.updateScore(10);
                // snake->setSpeed(speed += 2);
                std::cout << "Apple eaten!" << std::endl;
                grid->show(mp, apple_x, apple_y); // 显示网格
                snake->grow();
                apple.getRandomPosition(apple_x, apple_y);
                appleImg->show(mp, apple_x, apple_y);
            }
        }

        // 检查是否有暂停操作
        if (point->x() >= 0 && point->x() <= 60 && point->y() >= 0 && point->y() <= 36)
        {
            snake->setStatus(true);            // 暂停游戏
            system("killall -STOP madplay &"); // 停止播放背景音乐
            // usleep(200000);         // 防止误触，短暂休眠
        }

        // 检查是否有恢复操作
        if (point->x() >= 200 && point->x() <= 243 && point->y() >= 0 && point->y() <= 36)
        {
            snake->setStatus(false);           // 恢复游戏
            system("killall -CONT madplay &"); // 恢复播放背景音乐
            // usleep(200000);          // 防止误触，短暂休眠
        }

        // 检查是否加速
        if (point->x() >= 12 && point->x() <= 60 && point->y() >= 444 && point->y() <= 475)
        {
            snake->setSpeed(snake->getSpeed() + 1);
            // usleep(200000); // 防止误触，短暂休眠
        }

        // 检查是否减速
        if (point->x() >= 363 && point->x() <= 410 && point->y() >= 444 && point->y() <= 475)
        {
            snake->setSpeed(snake->getSpeed() - 1);
            // usleep(200000); // 防止误触，短暂休眠
        }
    }
    while (1)
    {
        // 检查是否重新开始游戏
        if (point->x() >= 713 && point->x() <= 790 && point->y() >= 444 && point->y() <= 474)
        {
            grid->show(mp, apple_x, apple_y);

            // 重新初始化蛇的位置和长度
            snake->reset(205, 270, 3, Direction::RIGHT, 1);
            score.resetScore();
            system("killall -9 madplay "); // 停止播放背景音乐
            snakeRunThread(snake, score);
            // apple.getRandomPosition(apple_x, apple_y);
            // appleImg->show(mp, apple_x, apple_y);
            // snake->setStatus(false); // 恢复游戏
            // snake->setSpeed(10);
            // usleep(200000);          // 防止误触，短暂休眠
        }
        // 检查是否退出游戏
        if (point->x() >= 740 && point->x() <= 790 && point->y() >= 7 && point->y() <= 36)
        {
            system("killall -9 madplay "); // 停止播放背景音乐
            status = 1;
            break;
        }
    }

    delete appleImg;
    delete grid;
}

int main()
{
    LCD *lcd = LCD ::getInstance();            // 初始化LCD
    TouchScreen *ts = TouchScreen::instance(); // 初始化触摸屏
    mp = lcd->lcdaddr();                       // 获取LCD的内存指针

    BMP *mainUi = new BMP("./img/mainUI.bmp"); // 初始化主界面
    mainUi->show(mp);                          // 显示主界面
    ShowFont *showFont = ShowFont::instance(); // 字体显示类实例
    Score score(showFont);                     // 分数类实例

    thread touchThread(touchScreenThread, ts, point); // 启动触摸屏线程

    thread snakeThread(snakeRunThread, &snake, score); // 启动蛇线程

    snakeThread.join();
    touchThread.join();

    return 0;
}