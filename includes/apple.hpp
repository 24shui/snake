#ifndef APPLE_HPP
#define APPLE_HPP

#include <cstdlib>
#include <ctime>

class Apple
{
private:
    int imageWidth;
    int imageHeight;
    int rectLeft;
    int rectTop;
    int rectRight;
    int rectBottom;

public:
    Apple(int imgWidth, int imgHeight, int left, int top, int right, int bottom);
    void getRandomPosition(int &x, int &y);
};

#endif // APPLE_HPP