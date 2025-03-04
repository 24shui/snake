#ifndef SCORE_H
#define SCORE_H

#include "showfont.hpp"
#include <cstring>

class Score
{
private:
    int scoreValue; // 分数值
    ShowFont *showFont;

public:
    Score(ShowFont *font); // 构造函数，初始化分数为 0
    ~Score();              // 析构函数

    void displayScore(int posXToLcd, int posYToLcd); // 显示分数
    void updateScore(int increment);                 // 更新分数，增加指定的增量
    void resetScore();                               // 重置分数为 0
    int getScore() const;                            // 获取当前分数
};

#endif // SCORE_H