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

void Slider::render()
{
    SDL_Rect r;
    r = {x + 1, y, w - 1, h - 1};
    fillRect(0xFF000000, r);
    
    r = {x + 2, y + 1, w, h - 2};
    fillRect(0xFF000000, r);
    
    r = { x + (int) ((float) (currentValue - minValue) * (float) w / (float) (maxValue - minValue)), y, 5, h };
    fillRect(0xFFF00000, r);
    
    drawTextAspect(std::to_string(currentValue).c_str(), 0xFFFFFFFF, {x, y, w, h}, textCache, needsUpdate);
    needsUpdate = false;
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
                needsUpdate = true;
                currentValue = (int)((float)((e.button.x / SCALE_X) - x) * (float)(maxValue - minValue) / (float) w + minValue);
                currentValue = currentValue >= maxValue ? maxValue : currentValue; // Min(current, max)
                if(clbck != nullptr) clbck(menu, currentValue);
            }
        }
    }
}
