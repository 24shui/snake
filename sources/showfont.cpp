#include "../includes/showfont.hpp"
#include "../includes/font.h"

ShowFont *ShowFont::m_instance = NULL;

// 构造函数
ShowFont::ShowFont()
{
    // 初始化ShowFont对象
}

// 析构函数，用于释放ShowFont对象所占用的资源
ShowFont::~ShowFont()
{
}

// 显示字体函数
int ShowFont::display(char *buf, int pixelsize, int backgroundWidth, int backgroundHeight, int backgroundColor, int fontColor, int posXToLcd, int posYToLcd)
{

    // 调用字体显示函数，传入参数为lcd对象、buf、pixelsize、backgroundWidth、backgroundHeight、backgroundColor、fontColor、posXToLcd、posYToLcd
    font_show(this->lcd, buf, pixelsize, backgroundWidth, backgroundHeight, backgroundColor, fontColor, posXToLcd, posYToLcd);
}

void ShowFont::font_show(LcdDevice *lcd, char *text, int pixelsize, int backgroundWidth, int backgroundHeight, int backgroundColor, int fontColor, int posXToLcd, int posYToLcd)
{
    // 打开字体
    font *f = fontLoad((char *)"/usr/share/fonts/DroidSansFallback.ttf");

    // 字体大小的设置
    fontSetSize(f, pixelsize);

    int bgc_red = backgroundColor >> 16;
    int bgc_green = (backgroundColor >> 8) & 0xff;
    int bgc_blue = backgroundColor & 0xff;
    // 创建一个画板（点阵图）
    bitmap *bm = createBitmapWithInit(backgroundWidth, backgroundHeight, 4, getColor(0, bgc_red, bgc_green, bgc_blue)); // 也可使用createBitmapWithInit函数，改变画板颜色
    // bitmap *bm = createBitmap(288, 100, 4);

    // 将字体写到点阵图上
    int font_red = fontColor >> 16;
    int font_green = (fontColor >> 8) & 0xff;
    int font_blue = fontColor & 0xff;
    fontPrint(f, bm, 0, 0, text, getColor(0, font_red, font_green, font_blue), 0);

    // 把字体框输出到LCD屏幕上
    show_font_to_lcd((unsigned int *)LCD::getInstance()->lcdaddr(), posXToLcd, posYToLcd, bm);

    // 关闭字体，关闭画板
    fontUnload(f);
    destroyBitmap(bm);
}

// 返回ShowFont类的单例实例
ShowFont *ShowFont::instance()
{
    // 如果单例实例为空，则创建一个新的实例
    if (m_instance == NULL)
    {
        m_instance = new ShowFont();
    }
    // 返回单例实例
    return m_instance;
}
