#include "Vec2.h"

Vec2::Vec2() {}

Vec2::Vec2(float vecx,float vecy)
: x(vecx),y(vecy)
{

}

Vec2 Vec2::operator + (const Vec2 & rightSide) const
{
    return Vec2(x+rightSide.x,y + rightSide.y);
}

Vec2 Vec2::operator - (const Vec2 & rightSide) const
{
    return Vec2(x+rightSide.x,y+rightSide.y);
}

Vec2 Vec2::operator * (const float &rightSide) const
{
    return Vec2(x*rightSide,y*rightSide);
}

Vec2 Vec2::operator / (const float & rightSide) const
{
    return Vec2(x / rightSide, y/rightSide);
}

Vec2 Vec2::operator += (const Vec2 & rightSide)
{
    x += rightSide.x;
    y += rightSide.y;
    return *this;
}

Vec2 Vec2::operator -= (const Vec2 & rightSide)
{
    x -= rightSide.x;
    y -= rightSide.y;
    return *this;
}

Vec2 Vec2::operator *= (const float &rightSide)
{
    x *= rightSide;
    y *= rightSide;
    return *this;
}

Vec2 Vec2::operator /= (const float & rightSide)
{
    x /= rightSide;
    y /= rightSide;
    return *this;
}


bool Vec2::operator==(const Vec2 &rightSide) const
{
    return (x == rightSide.x && y == rightSide.y);
}

bool Vec2::operator!=(const Vec2 &rightSide) const
{
    return (x != rightSide.x || y != rightSide.y);
}
