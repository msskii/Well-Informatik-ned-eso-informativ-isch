//
//  Button.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Button.hpp"

Button::Button(buttonClickHandler bhandler, const char* t, int _x, int _y, int _w, int _h, int bid) : handler(bhandler), x(_x), y(_y), w(_w), h(_h), text(t)
{
	elementID = bid;
}

void Button::render(SDL_Renderer *renderer)
{
    if(!menu->active) hoverOver = false;
    
    SDL_Rect r = {x, y, w, h};
    COLOR(renderer, (hoverOver ? 0xFF777777 : 0xFFFFFFFF)); // Full white or grayish... TODO: Textures
    SDL_RenderFillRect(renderer, &r);
    
    drawTextAspect(renderer, text, 0xFFFF00FF, x, y, w, h);
}

void Button::processEvent(Menu* menu, SDL_Event e)
{
    if(e.type == SDL_MOUSEMOTION)
    {
        hoverOver = menu->active && e.button.x / SCALE_X >= x && e.button.x / SCALE_X <= x + w && e.button.y / SCALE_Y >= y && e.button.y / SCALE_Y <= y + h;
    }
    else if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        hoverOver = menu->active && e.button.x / SCALE_X >= x && e.button.x / SCALE_X <= x + w && e.button.y / SCALE_Y >= y && e.button.y / SCALE_Y <= y + h;
        if(e.button.button == SDL_BUTTON_LEFT && hoverOver)
        {
            clicked = true;
            if(handler != nullptr) handler(menu, this);
        }
    }
}
