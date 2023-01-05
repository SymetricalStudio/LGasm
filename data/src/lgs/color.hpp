#ifndef __LGASM_COLOR_H__
#define __LGASM_COLOR_H__

#include <SDL2/SDL.h>

struct uLG_Color
{
    int r, g, b;
};

class LG_Color
{
    private:
        int r, g, b;

    public:
        LG_Color(int _r, int _g, int _b);
        LG_Color();
        uLG_Color GetColor();
};

#endif