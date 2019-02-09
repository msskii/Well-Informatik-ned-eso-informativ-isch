//
//  KeyConfigBox.cpp
//  Informatik
//
//  Created by Aaron Hodel on 25.10.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "KeyConfigBox.hpp"
#include "../graphics/overlay/Menu.hpp"

KeyConfigBox::KeyConfigBox(SDL_Keycode code, int x, int y, int w, int h, int id) : TextBox("", x, y, w, h, id)
{
    const char * name = SDL_GetKeyName(code);
    toStore = std::to_string(code); // Store the code as int
    currentText = std::string(" Key:  ") + name;
}

void KeyConfigBox::processEvent(Menu *menu, SDL_Event e)
{
    if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        hoverOver = menu->active && e.button.x / SCALE_X >= x && e.button.x / SCALE_X <= x + w && e.button.y / SCALE_Y >= y && e.button.y / SCALE_Y <= y + h;
        
        if(hoverOver) focus = true;
        else focus = false;
    }
    else if(e.type == SDL_KEYDOWN && focus)
    {
        currentText = std::string(" Key:  ") + SDL_GetKeyName(e.key.keysym.sym);
        toStore = std::to_string(e.key.keysym.sym); // Store the code as int
    }
}

