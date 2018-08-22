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

void Button::render(SDL_Renderer *renderer)
{
    SDL_Rect r = {x, y, w, h};
    COLOR(renderer, 0xFFFFFFFF); // Full white
    SDL_RenderFillRect(renderer, &r);
}

void Button::processEvent(SDL_Event e)
{
    
}
