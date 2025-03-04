#ifndef SHOWFONT_H
#define SHOWFONT_H

#include "./lcd.hpp"
extern "C"
{
#include "font.h"
}

class ShowFont
{
public:
    enum Color
    {
        red = 0x00FF0000,          /* 红色 */
        bule = 0x000000FF,         /* 蓝色 */
        Lime = 0x0000FF00,         /* 酸橙色(绿) */
        white = 0x00FFFFFF,        /* 白色 */
        purple = 0x00800080,       /* 紫色 */
        yellow = 0x00FFFF00,       /* 黄色 */
        khaki = 0x00F0E68C,        /* 卡其布色 */
        gold = 0x00FFD700,         /* 金色 */
        chocolate = 0x00D2691E,    /* 巧克力色 */
        tomato = 0x00FF6347,       /* 番茄色 */
        black = 0x00000000,        /* 黑色 */
        darkSeaGreen = 0x008FBC8F, /* 深海洋绿 */
        oliveDrab = 0x00556B2F,    /* 橄榄土褐色 */
        darkSlateGray = 0x002F4F4F /* 深石板灰 */
    };

private:
    struct LcdDevice *lcd;
    static ShowFont *m_instance;

public:
    ~ShowFont(); // 析构函数

    int display(char *buf, int pixelsize, int backgroundWidth, int backgroundHeight, int backgroundColor, int fontColor, int posXToLcd, int posYToLcd); // 显示函数

    void font_show(struct LcdDevice *lcd, char *text, int pixelsize, int backgroundWidth, int backgroundHeight, int backgroundColor, int fontColor, int posXToLcd, int posYToLcd); // 字体显示函数

    static ShowFont *instance(); // 单例模式

private:
    ShowFont(); // 构造函数
};

#endif // SHOWFONT_H
