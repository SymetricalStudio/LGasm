#ifndef __LGASM_OBJECT_H__
#define __LGASM_OBJECT_H__

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class LG_Rect
{
    private:
        SDL_Rect rect;

    public:
        LG_Rect(int x, int y, int w, int h);
        SDL_Rect* GetRect();
        void ChangeSize(int w, int h);
        void ChangePosition(int x, int y);
        void MovePosition(int x, int y);
};

#endif