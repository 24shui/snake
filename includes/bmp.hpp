#ifndef __BMP_HPP__
#define __BMP_HPP__

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "lcd.hpp"

class BMP
{
public:
    BMP(const char *bmp_path); // 构造函数，根据路径打开图片文件
    ~BMP();                    // 析构函数，关闭图片文件

    // 根据索引返回图片像素数据
    char operator[](int index);

    // 返回图片数据的首地址
    char *addr() const;

    // 根据坐标把图片数据写如到一个映射内存中
    int show(int *mp, int x = 0, int y = 0);

    // 提取图片宽高
    int width() const;
    int height() const;

private:
    int fd;            /* 图片文件描述符 */
    int pic_width;     /* 图片宽度 */
    int pic_height;    /* 图片高度 */
    int pic_size;      /* 图片大小 */
    char *pic_buf_ptr; /* 图片数据指针 */
};

#endif