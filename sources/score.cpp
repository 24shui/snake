#include "../includes/score.hpp"

// 构造函数，初始化分数为 0
Score::Score(ShowFont *font) : scoreValue(0), showFont(font)
{
}

// 析构函数
Score::~Score()
{
}

// 显示分数
// 在LCD上显示分数
void Score::displayScore(int posXToLcd, int posYToLcd)
{
    // 定义一个字符数组，用于存储分数字符串
    char scoreStr[20];
    // 将分数值转换为字符串，并存储在scoreStr数组中
    snprintf(scoreStr, sizeof(scoreStr), "分数: %d", scoreValue);
    // 调用showFont对象的display方法，在LCD上显示分数字符串
    showFont->display(scoreStr, 24, 200, 50, 0x00faebd7, ShowFont::black, posXToLcd, posYToLcd);
}

// 更新分数，增加指定的增量
void Score::updateScore(int increment)
{
    scoreValue += increment;
}

// 重置分数为 0
void Score::resetScore()
{
    scoreValue = 0;
}

// 获取当前分数
int Score::getScore() const
{
    return scoreValue;
}