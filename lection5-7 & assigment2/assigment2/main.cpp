#include <iostream>
#include "Vec2.h"

int main() {

    Vec2 a(500,200);
    Vec2 b(100,50);
    a += b;
    std::cout <<  a.x << std::endl;
    return 0;
}
