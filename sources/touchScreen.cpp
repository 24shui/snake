#include "../includes/touchScreen.hpp"

TouchScreen *TouchScreen::m_instance = nullptr;
int TouchScreen::fd = -1;

// 构造函数，打开触摸屏设备文件
TouchScreen::TouchScreen()
{
    this->fd = open(TS_PATH, O_RDONLY | O_NONBLOCK);
    if (this->fd < 0)
    {
        perror("打开触摸屏失败");
        exit(1);
    }
}

// 析构函数，用于释放TouchScreen对象占用的资源
TouchScreen::~TouchScreen()
{
    if (fd != -1)
    {
        close(fd);
    }
}

// 返回TouchScreen类的实例
TouchScreen *TouchScreen::instance()
{
    if (m_instance == nullptr)
    {
        m_instance = new TouchScreen();
    }
    return m_instance;
}

// 删除TouchScreen实例
void TouchScreen::del_instance()
{
    if (fd != -1)
    {
        ::close(fd);
    }
    delete m_instance;
    m_instance = nullptr;
}

// 判断手势类型的函数
GestureType getGestureType(int startX, int startY, int endX, int endY)
{
    int dx = endX - startX;
    int dy = endY - startY;
    int absDx = std::abs(dx);
    int absDy = std::abs(dy);

    if (absDx >= MIN_SWIPE_DISTANCE || absDy >= MIN_SWIPE_DISTANCE)
    {
        if (absDx > absDy)
        {
            if (dx > 0)
            {
                cout << "向右滑动" << endl;
                return SWIPE_RIGHT;
            }
            else
            {
                cout << "向左滑动" << endl;
                return SWIPE_LEFT;
            }
        }
        else
        {
            if (dy > 0)
            {
                cout << "向下滑动" << endl;
                return SWIPE_DOWN;
            }
            else
            {
                cout << "向上滑动" << endl;
                return SWIPE_UP;
            }
        }
    }
    cout << "点击" << endl;
    return CLICK;
}

GestureType TouchScreen::wait(Points &p)
{
    int startX = 0, startY = 0;
    int endX = 0, endY = 0;
    bool isPressed = false;

    while (1)
    {
        struct input_event info;
        ssize_t bytesRead = read(this->fd, &info, sizeof(struct input_event));
        if (bytesRead <= 0)
        {
            continue;
        }

        if (info.type == EV_KEY && info.code == BTN_TOUCH && info.value == 1)
        {
            isPressed = true;
        }

        if (info.type == EV_KEY && info.code == BTN_TOUCH && info.value == 0)
        {
            isPressed = false;
            endX = p.x();
            endY = p.y();

            GestureType gesture = getGestureType(startX, startY, endX, endY);
            return gesture;
        }

        if (info.type == EV_ABS && info.code == ABS_X)
        {
            p.setX(info.value);
            if (isPressed && startX == 0)
            {
                startX = info.value;
            }
        }
        if (info.type == EV_ABS && info.code == ABS_Y)
        {
            p.setY(info.value);
            if (isPressed && startY == 0)
            {
                startY = info.value;
            }
        }
    }
    return NONE;
}