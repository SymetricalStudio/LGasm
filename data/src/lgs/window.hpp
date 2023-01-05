#ifndef __LGASM_WINDOW_H__
#define __LGASM_WINDOW_H__

#include <SDL2/SDL.h>
#include "color.hpp"
#include "object.hpp"

class LG_Window
{
    private:
        SDL_Window* window;
        SDL_Renderer* render;
        SDL_Event event;

    public:
        LG_Window(const char* title);
        LG_Window();
        void SetData(const char* title);
        SDL_Window* GetWindow();
        SDL_Renderer* GetRenderer();
        bool IsOpen = true;
        void Delay(int ms);
        void PollEvent();
        void Clear(uLG_Color* color);
        void Draw(LG_Rect* rect, uLG_Color* color);
        void Update();
};

#endif