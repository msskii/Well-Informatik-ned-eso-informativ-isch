//
//  Button.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Button.hpp"

Button::Button(buttonClickHandler bhandler, const char* t, int _x, int _y, int _w, int _h) : handler(bhandler), x(_x), y(_y), w(_w), h(_h), text(t)
{
    
}

Button::Button(buttonClickHandler bhandler, const char* t, int _x, int _y, int _w, int _h, int bid) : handler(bhandler), x(_x), y(_y), w(_w), h(_h), text(t), id(bid)
{
    
}

void Button::render(SDL_Renderer *renderer)
{
    SDL_Rect r = {x, y, w, h};
    COLOR(renderer, (hoverOver ? 0xFF777777 : 0xFFFFFFFF)); // Full white or grayish... TODO: Textures
    SDL_RenderFillRect(renderer, &r);
    
    drawText(renderer, text, 0xFFFF00FF, x, y, w, h);
}

void Button::processEvent(Menu* menu, SDL_Event e)
{
    if(e.type == SDL_MOUSEMOTION)
    {
        hoverOver = e.button.x >= x && e.button.x <= x + w && e.button.y >= y && e.button.y <= y + h;
    }
    else if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        hoverOver = e.button.x >= x && e.button.x <= x + w && e.button.y >= y && e.button.y <= y + h;
        if(e.button.button == SDL_BUTTON_LEFT && hoverOver)
        {
            clicked = true;
            if(handler != nullptr) handler(menu, id);
        }
    }
}
