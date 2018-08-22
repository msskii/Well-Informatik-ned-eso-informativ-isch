//
//  Button.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Button.hpp"

Button::Button(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h)
{
    
}

Button::Button(int _x, int _y, int _w, int _h, int bid) : x(_x), y(_y), w(_w), h(_h), id(bid)
{
    
}

void Button::render(SDL_Renderer *renderer)
{
    SDL_Rect r = {x, y, w, h};
    COLOR(renderer, (hoverOver ? 0xFF777777 : 0xFFFFFFFF)); // Full white or grayish... TODO: Textures
    SDL_RenderFillRect(renderer, &r);
    
    drawText(renderer, "Button Test Text", {0xFF, 0x00, 0xFF, 0xFF}, x, y);
}

void Button::processEvent(Menu* menu, SDL_Event e)
{
    if(e.type == SDL_MOUSEMOTION)
    {
        hoverOver = e.button.x >= x && e.button.x <= x + w && e.button.y >= y && e.button.y <= y + h;
    }
}
