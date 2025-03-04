#ifndef __LCD_HPP__
#define __LCD_HPP__

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

#define LCD_PATH "/dev/fb0"

// 单实例模式
class LCD
{
    LCD(); // 构造函数
public:
    ~LCD();                          // 析构函数
    void init(const char *lcd_path); // 初始化lcd

    int *lcdaddr();
    int getFd() const;

    // 创建和删除实例
    static LCD *getInstance();
    static void destroyInstance();

private:
    int fd;                 /* 文件描述符 */
    int *m_ptr;             /* 屏幕内存映射 */
    static LCD *m_instance; /* 单例实例对象空间指针 */
};

#endif // __LCD_H__
