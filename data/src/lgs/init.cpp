#include "init.hpp"

int LG_Init()
{
    return SDL_Init(SDL_INIT_EVERYTHING);
}

int LG_End()
{
    return 0;
}

