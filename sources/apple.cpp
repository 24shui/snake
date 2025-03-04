#include "../includes/apple.hpp"

// 构造函数，初始化图片尺寸和矩形区域信息
Apple::Apple(int imgWidth, int imgHeight, int left, int top, int right, int bottom)
    : imageWidth(imgWidth), imageHeight(imgHeight), rectLeft(left), rectTop(top), rectRight(right), rectBottom(bottom)
{
    // 初始化随机数种子
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

// 获取图片在矩形区域内的随机合法位置
void Apple::getRandomPosition(int &x, int &y)
{
    // 计算 x 坐标的合法范围
    int maxX = rectRight - imageWidth;
    // 计算 y 坐标的合法范围
    int maxY = rectBottom - imageHeight;

    // 确保矩形区域能够容纳图片
    if (maxX >= rectLeft && maxY >= rectTop)
    {
        // 生成随机的 x 坐标
        x = rectLeft + std::rand() % (maxX - rectLeft + 1);
        // 生成随机的 y 坐标
        y = rectTop + std::rand() % (maxY - rectTop + 1);
    }
    else
    {
        // 如果矩形区域无法容纳图片，将坐标设为左上角
        x = rectLeft;
        y = rectTop;
    }
}