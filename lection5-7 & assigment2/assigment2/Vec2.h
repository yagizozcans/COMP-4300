//
// Created by Yağız Özcan on 12.02.2024.
//

class Vec2
{
public:
    float x = 0;
    float y = 0;

    Vec2();
    Vec2(float vecx,float vecy);

    bool operator == (const Vec2 & rightSide) const;
    bool operator != (const Vec2 & rightSide) const;

    Vec2 operator + (const Vec2 & rightSide) const;
    Vec2 operator - (const Vec2 & rightSide) const;
    Vec2 operator / (const float & rightSide) const;
    Vec2 operator * (const float & rightSide) const;

    Vec2 operator += (const Vec2 & rightSide);
    Vec2 operator -= (const Vec2 & rightSide);
    Vec2 operator *= (const float & rightSide);
    Vec2 operator /= (const float & rightSide);
};
