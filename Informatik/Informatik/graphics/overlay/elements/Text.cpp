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

void Text::render()
{
    fillRect(0xFFFFFFFF, {x, y, w, h});
    if(texture.id == 0) drawTextAspect(text, 0xFFFF00FF, {x, y, w, h}, texture, false);
    else renderWithoutShading(texture.getGL(), {}, {x, y, w, h});
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

void DebugText::render()
{
    const char *ns = updater(menu, this);
    drawTextAspect(ns, 0xFFFF00FF, {x, y, w, h}, texture, std::string(ns) != os);
    os = std::string(ns);

}

void DebugText::processEvent(Menu *menu, SDL_Event e)
{
    
}
