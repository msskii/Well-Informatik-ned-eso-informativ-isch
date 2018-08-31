//
//  Slider.cpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Slider.hpp"

Slider::Slider(int min, int max, int _x, int _y, int _w, int _h, int id) : minValue(min), maxValue(max)
{
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    elementID = id;
}

Slider::Slider(int min, int max, int current, int _x, int _y, int _w, int _h, int id) : minValue(min), maxValue(max), currentValue(current)
{
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    elementID = id;
}

void Slider::render(SDL_Renderer *renderer)
{
    SDL_Rect r = { x + (int) ((float) (currentValue - minValue) * (float) w / (float) (maxValue - minValue)), y, 5, h };
    COLOR(renderer, 0xFFF00000);
    SDL_RenderFillRect(renderer, &r);
    
    COLOR(renderer, 0xFF000000);

    drawTextAspect(renderer, std::to_string(currentValue).c_str(), 0xFF000000, x, y, w, h);
    
    r = {x + 1, y, w - 1, h - 1};
    SDL_RenderDrawRect(renderer, &r);
    
    r = {x + 2, y + 1, w, h - 2};
    SDL_RenderDrawRect(renderer, &r);
}

void Slider::processEvent(Menu *menu, SDL_Event e)
{
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
    {
        if(e.button.button == SDL_BUTTON_LEFT)
        {
            bool isOver = e.button.x / SCALE_X >= x && e.button.x / SCALE_X - 10 <= x + w && e.button.y / SCALE_Y >= y && e.button.y / SCALE_Y <= y + h;
            if(isOver)
            {
                currentValue = (int)((float)((e.button.x / SCALE_X) - x) * (float)(maxValue - minValue) / (float) w + minValue);
                currentValue = currentValue >= maxValue ? maxValue : currentValue; // Min(current, max)
                if(clbck != nullptr) clbck(menu, currentValue);
            }
        }
    }
}
