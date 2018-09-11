//
//  Text.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Text.hpp"

Text::Text(const char* t, int _x, int _y, int _w, int _h) : text(t)
{
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

void Text::render(SDL_Renderer *renderer)
{
    if(texture.texture == nullptr) drawTextAspect(renderer, text, 0xFFFF00FF, x, y, w, h, texture);
    else
    {
        SDL_Rect r = {x, y, w, h};
        SDL_RenderCopy(renderer, texture.texture, NULL, &r);
    }
}

void Text::processEvent(Menu *menu, SDL_Event e)
{
    
}

DebugText::DebugText(const char *frmt, int ml, textUpdate u, int _x, int _y, int _w, int _h, int id) : format(frmt), maxLength(ml), updater(u)
{
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    buffer = (char*) malloc(ml + 1); // Max length + null terminator
	elementID = id;
}

void DebugText::render(SDL_Renderer *renderer)
{
    const char *ns = updater(menu, this);
    if(texture.texture == nullptr || std::string(ns) != os)
    {
        drawTextAspect(renderer, ns, 0xFF000000, x, y, w, h, texture);
        os = std::string(ns);
    }
    else
    {
        SDL_Rect r = {x, y, w, h};
        SDL_RenderCopy(renderer, texture.texture, NULL, &r);
    }
}

void DebugText::processEvent(Menu *menu, SDL_Event e)
{
    
}
