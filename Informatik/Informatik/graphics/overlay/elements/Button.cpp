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

void Button::render(SDL_Renderer *renderer)
{
    if(!menu->active) hoverOver = false;
    
    SDL_Rect r = {x, y, w, h};
    
    int texture = clicked ? BUTTON_CLICKED : hoverOver ? BUTTON_HOVER : BUTTON_NORMAL;
    if(textures[texture] == nullptr)
    {
        printf("No texture\n");
    }
    SDL_RenderCopy(renderer, textures[texture], NULL, &r);
    
    if(button_texture.texture == nullptr) drawTextCentered(renderer, text, 0xFFFF00FF, x, y, w, h, button_texture);
    else
    {
        r = {x, y, button_texture.textwidth, button_texture.textheight};
        r.x += (int)((w - button_texture.textwidth) / 2.0);
        r.y += (int)((h - button_texture.textheight) / 2.0);
        SDL_RenderCopy(renderer, button_texture.texture, NULL, &r);
    }
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
