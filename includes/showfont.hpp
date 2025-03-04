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
        red = 0x00FF0000,          /* ��ɫ */
        bule = 0x000000FF,         /* ��ɫ */
        Lime = 0x0000FF00,         /* ���ɫ(��) */
        white = 0x00FFFFFF,        /* ��ɫ */
        purple = 0x00800080,       /* ��ɫ */
        yellow = 0x00FFFF00,       /* ��ɫ */
        khaki = 0x00F0E68C,        /* ���䲼ɫ */
        gold = 0x00FFD700,         /* ��ɫ */
        chocolate = 0x00D2691E,    /* �ɿ���ɫ */
        tomato = 0x00FF6347,       /* ����ɫ */
        black = 0x00000000,        /* ��ɫ */
        darkSeaGreen = 0x008FBC8F, /* ����� */
        oliveDrab = 0x00556B2F,    /* �������ɫ */
        darkSlateGray = 0x002F4F4F /* ��ʯ��� */
    };

private:
    struct LcdDevice *lcd;
    static ShowFont *m_instance;

public:
    ~ShowFont(); // ��������

    int display(char *buf, int pixelsize, int backgroundWidth, int backgroundHeight, int backgroundColor, int fontColor, int posXToLcd, int posYToLcd); // ��ʾ����

    void font_show(struct LcdDevice *lcd, char *text, int pixelsize, int backgroundWidth, int backgroundHeight, int backgroundColor, int fontColor, int posXToLcd, int posYToLcd); // ������ʾ����

    static ShowFont *instance(); // ����ģʽ

private:
    ShowFont(); // ���캯��
};

#endif // SHOWFONT_H
