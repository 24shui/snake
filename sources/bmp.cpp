#include "../includes/bmp.hpp"

BMP::BMP(const char *bmp_path)
{
    // 打开图片文件
    this->fd = open(bmp_path, O_RDONLY);
    if (this->fd == -1)
    {
        // 打开图片文件失败，输出错误信息并退出程序
        perror("图片打开失败");
        exit(EXIT_FAILURE);
    }

    // 将文件指针移动到文件的第18个字节处，即图片宽度所在的字节位置
    lseek(this->fd, 18, SEEK_SET);
    // 从文件中读取图片宽度，并存储到m_width变量中
    read(this->fd, &this->pic_width, sizeof(int));
    // 从文件中读取图片高度，并存储到m_height变量中
    read(this->fd, &this->pic_height, sizeof(int));

    // 获取图片数据大小
    this->pic_size = this->pic_height * this->pic_width * 3;

    // 申请空间存放图片数据，不读取补齐的字节
    this->pic_buf_ptr = new char[this->pic_size];

    // 计算补齐字节数
    int skip_byte = 0;
    if (this->pic_width * 3 % 4 != 0)
    {
        skip_byte = 4 - (this->pic_width * 3 % 4);
    }

    // 将文件指针移动到文件的第54个字节处，即图片数据所在的字节位置
    lseek(this->fd, 54, SEEK_SET);

    // 倒置存放图片数据
    char *tmp_ptr = this->pic_buf_ptr;
    tmp_ptr += this->pic_size;

    for (int i = 0; i < this->pic_height; i++)
    {
        tmp_ptr -= this->pic_width * 3;               // 每次减去一行,从下往上读取
        read(this->fd, tmp_ptr, this->pic_width * 3); // 读取一行数据
        lseek(this->fd, skip_byte, SEEK_CUR);         // 跳过每行的补齐字节，不读取他们
    }
    ::close(this->fd);
}

// 析构函数，释放内存
BMP::~BMP()
{
    // 释放图片缓冲区指针指向的内存
    delete[] this->pic_buf_ptr;
}

// 重载[]运算符，返回pic_buf_ptr指针指向的数组中index位置的字符
char BMP::operator[](int index)
{
    return this->pic_buf_ptr[index];
}

// 返回指向BMP图片缓冲区的指针
char *BMP::addr() const
{
    return this->pic_buf_ptr;
}

int BMP::show(int *mp, int x, int y)
{

    // 遍历图片的每一行
    for (int i = 0, n = 0; i < this->pic_height; i++)
    {
        // 遍历图片的每一列
        for (int j = 0; j < this->pic_width; j++, n += 3)
        {
            // 将图片的RGB值转换为整数，并存储到显示缓冲区中
            *(mp + 800 * (i + y) + j + x) = this->pic_buf_ptr[n] << 0 | this->pic_buf_ptr[n + 1] << 8 | this->pic_buf_ptr[n + 2] << 16;
        }
    }
    return 0;
}

// 返回BMP图片的宽度
int BMP::width() const
{
    return pic_width;
}

// 返回图片的高度
int BMP::height() const
{
    return pic_height;
}
