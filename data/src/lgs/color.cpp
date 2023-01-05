#include "color.hpp"

#include <iostream>

LG_Color::LG_Color(int _r, int _g, int _b)
{
    r, g, b = _r, _g, _b;

    std::cout << r << " " << g << " " << b << std::endl;
}

LG_Color::LG_Color()
{
    r, g, b = 0;
}

uLG_Color LG_Color::GetColor()
{
    uLG_Color color = {r, g, b};

    return color;
}