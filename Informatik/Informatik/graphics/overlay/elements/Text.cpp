//
//  Text.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Text.hpp"

Text::Text(const char* t, int _x, int _y, int _w, int _h) : text(t), x(_x), y(_y), w(_w), h(_h)
{
    
}

void Text::render(SDL_Renderer *renderer)
{
    drawText(renderer, text, 0xFFFF00FF, x, y, w, h);
}

void Text::processEvent(Menu *menu, SDL_Event e)
{
    
}
