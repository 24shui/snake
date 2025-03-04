#include "../includes/lcd.hpp"

LCD::LCD()
{
    init(LCD_PATH);
}

LCD::~LCD()
{
    // 关闭设备文件
    ::close(this->fd);
    // 解除内存映射
    int ret = munmap(this->m_ptr, 800 * 480 * 4);
    if (ret)
    {
        perror("解除映射失败");
    }
    // 释放实例空间
    delete[] this->m_instance;
    this->m_instance = NULL;
}

// 获取LCD的文件描述符
int LCD::getFd() const
{
    // 返回文件描述符
    return fd;
}

// 返回LCD类的m_ptr指针
int *LCD::lcdaddr()
{
    return this->m_ptr;
}

void LCD::init(const char *lcd_path)
{
    // 设置lcd_path为"/dev/fb0"
    lcd_path = "/dev/fb0";

    // 打开设备文件
    this->fd = open(lcd_path, O_RDWR);
    if (this->fd == -1)
    {
        perror("lcd打开失败");
    }

    // 创建映射
    this->m_ptr = (int *)mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, this->fd, 0);
    if (this->m_ptr == MAP_FAILED)
    {
        perror("内存映射失败");
    }
}

LCD *LCD::m_instance = nullptr;

LCD *LCD::getInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new LCD();
    }
    return m_instance;
}

void LCD::destroyInstance()
{
    // 关闭设备文件
    ::close(m_instance->fd);
    // 解除映射
    int ret = munmap(m_instance->m_ptr, 800 * 480 * 4);
    if (ret)
    {
        perror("解除映射失败");
    }
    // 释放实例空间
    delete[] m_instance;
    m_instance = NULL;
}