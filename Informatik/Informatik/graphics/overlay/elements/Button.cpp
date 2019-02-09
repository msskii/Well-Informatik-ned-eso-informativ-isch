//
//  Button.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Button.hpp"
#include "../Menu.hpp"

Button::Button(buttonClickHandler bhandler, const char* t, int _x, int _y, int _w, int _h, int bid) : handler(bhandler), text(t)
{
    x = _x;
    y = _y;
    w = _w;
    h = _h;
	elementID = bid;
}

void Button::render()
{
    if(!menu->active) hoverOver = false;
    
    SDL_Rect r = {x, y, w, h};
    
    int texture = clicked ? BUTTON_CLICKED : hoverOver ? BUTTON_HOVER : BUTTON_NORMAL;    
    renderWithoutShading(gl_textures[texture], {}, r);
    
    drawTextCentered(text, 0xFFFF00FF, {x, y, w, h});
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
            consumeEvent = true;

            clicked = true;
            if(handler != nullptr) handler(menu, this);
        }
    }
    if(!hoverOver) clicked = false;
}
