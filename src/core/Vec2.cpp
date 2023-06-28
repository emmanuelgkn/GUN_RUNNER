#include "Vec2.h"
#include<iostream>
#include <string.h>
#include <cassert>
using namespace std;

Vec2::Vec2() {

}

Vec2::Vec2(int x_, int y_)
{
    assert(x_ >= 0);
    assert(y_ >= 0);
    x = x_;
    y = y_;
}

Vec2::~Vec2()
{

}

int Vec2::getx() const
{
    return x;
}

int Vec2::gety() const
{
    return y;
}

void Vec2::setxy(int x_, int y_)
{
    x = x_;
    y = y_;
}
