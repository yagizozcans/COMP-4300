//
// Created by Yağız Özcan on 12.02.2024.
//

#include "Vec2.h"
#include <SFML/Graphics.hpp>

class CTransform
{
public:
    Vec2 pos = {0.0,0.0};
    Vec2 vel = {0.0,0.0};
    float angle = 0;
    CTransform(const Vec2 & p, const Vec2& v, float a)
    : pos(p),vel(v),angle(a)
    {
    }
};

class CShape
{
public:
    sf::CircleShape circle;
    CShape(float radius, int points, const sf::Color & fill, const sf::Color & outline, float thickness)
    : circle(radius,points)
    {
        circle.setFillColor(fill);
        circle.setOutlineColor(outline);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(radius,radius);
    }
};

class CCollision
{
public:
    float radius = 0;
    CCollision(float r)
    : radius(r) {}
};

class CScore
{
public:
    int score = 0;
    CScore(int s)
    : score(s) {}
};

class CLifespan
{
public:
    float remaining = 0;
    float total = 0;
    CLifespan(float total)
    : total(total),remaining(total) {}
};

class CInput
{
public:
    bool upKey = false;
    bool downKey = false;
    bool rightKey = false;
    bool leftKey = false;
    bool shoot = false;
    CInput(){}
};