#define SDL_MAIN_HANDLED
#include "lgasm.hpp"
#include <iostream>

LG_Window::LG_Window(const char* title)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 512, 512, SDL_WINDOW_ALLOW_HIGHDPI);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

LG_Window::LG_Window()
{

}

void LG_Window::SetData(const char* title)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 512, 512, SDL_WINDOW_ALLOW_HIGHDPI);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Window* LG_Window::GetWindow()
{
    return window;
}

SDL_Renderer* LG_Window::GetRenderer()
{
    return render;
}

void LG_Window::Delay(int ms)
{
    SDL_Delay(ms);
}

void LG_Window::PollEvent()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        IsOpen = false;
        break;
    
    default:
        IsOpen = true;
        break;
    }
}

void LG_Window::Clear(uLG_Color* color)
{
    uLG_Color* c = color;

    SDL_SetRenderDrawColor(render, (Uint8)c->r, (Uint8)c->g, (Uint8)c->b, 255);
    SDL_RenderClear(render);
}

void LG_Window::Draw(LG_Rect* rect, uLG_Color* color)
{
    uLG_Color* c = color;

    SDL_Rect* _rect = rect->GetRect();
    //std::cout << _rect->x << " " << _rect->y << " " << _rect->w << " " << _rect->h << std::endl;

    SDL_SetRenderDrawColor(render, (Uint8)c->r, (Uint8)c->g, (Uint8)c->b, 255);
    SDL_RenderFillRect(render, _rect);

}

void LG_Window::Update()
{
    SDL_RenderPresent(render);
}