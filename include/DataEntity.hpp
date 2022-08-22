#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "DataEntity.hpp"

class DataEntity
{
    public:
        int value;
        SDL_Rect rect;
        SDL_Color color = {255,255,255,255};

        DataEntity(int _value, int _y);
};