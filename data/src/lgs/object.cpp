#include "object.hpp"

const int PIXEL_SIZE = 8;

LG_Rect::LG_Rect(int x, int y, int w, int h)
{
    SDL_Rect _rect = {
        x * PIXEL_SIZE,
        y * PIXEL_SIZE,
        w * PIXEL_SIZE,
        h * PIXEL_SIZE
    };
    rect = _rect;
}

SDL_Rect* LG_Rect::GetRect()
{
    return &rect;
}

void LG_Rect::ChangeSize(int w, int h)
{
    rect.w = w * PIXEL_SIZE;
    rect.h = h * PIXEL_SIZE;
}

void LG_Rect::ChangePosition(int x, int y)
{
    rect.x = x * PIXEL_SIZE;
    rect.y = y * PIXEL_SIZE;
}

void LG_Rect::MovePosition(int x, int y)
{
    rect.x += x * PIXEL_SIZE;
    rect.y += y * PIXEL_SIZE;
}