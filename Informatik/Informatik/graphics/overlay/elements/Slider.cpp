//
//  Slider.cpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Slider.hpp"

Slider::Slider(int min, int max, int _x, int _y, int _w, int _h, int id) : minValue(min), maxValue(max), x(_x), y(_y), w(_w), h(_h)
{
    elementID = id;
}

Slider::Slider(int min, int max, int current, int _x, int _y, int _w, int _h, int id) : minValue(min), maxValue(max), currentValue(current), x(_x), y(_y), w(_w), h(_h)
{
    elementID = id;
}

void Slider::render(SDL_Renderer *renderer)
{
    SDL_Rect r = { x + (int) ((float) (currentValue - minValue) * (float) w / (float) (maxValue - minValue)), y, 5, h };
    COLOR(renderer, 0xFF000000);
    SDL_RenderFillRect(renderer, &r);
    
    drawTextAspect(renderer, std::to_string(currentValue).c_str(), 0xFF000000, x, y, w, h);
}

void Slider::processEvent(Menu *menu, SDL_Event e)
{
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
    {
        if(e.button.button == SDL_BUTTON_LEFT)
        {
            bool isOver = e.button.x / SCALE_X >= x && e.button.x / SCALE_X <= x + w && e.button.y / SCALE_Y >= y && e.button.y / SCALE_Y <= y + h;
            if(isOver) currentValue = (float)((e.button.x / SCALE_X) - x) * (float)(maxValue - minValue) / (float)w + minValue;
        }
    }
}
