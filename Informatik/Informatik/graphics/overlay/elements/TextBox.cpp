//
//  TextBox.cpp
//  Informatik
//
//  Created by Aaron Hodel on 24.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "TextBox.hpp"

TextBox::TextBox(const char *defaultText, int _x, int _y, int _w, int _h) : currentText(std::string(defaultText)), x(_x), y(_y), w(_w), h(_h)
{
    
}

void TextBox::render(SDL_Renderer *renderer)
{
    drawText(renderer, currentText.c_str(), 0xFF000000, x, y, w, h);
}

void TextBox::processEvent(Menu *menu, SDL_Event e)
{
    if(e.type == SDL_MOUSEMOTION)
    {
        hoverOver = menu->active && e.button.x / SCALE_X >= x && e.button.x / SCALE_X <= x + w && e.button.y / SCALE_Y >= y && e.button.y / SCALE_Y <= y + h;
    }
    else if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        hoverOver = menu->active && e.button.x / SCALE_X >= x && e.button.x / SCALE_X <= x + w && e.button.y / SCALE_Y >= y && e.button.y / SCALE_Y <= y + h;
        
        if(hoverOver) focus = true;
        else focus = false;
    }
    else if(e.type == SDL_KEYDOWN && focus)
    {
        //e.key.keysym.scancode
        if(defaultText) // Clear current text
        {
            currentText = "";
            defaultText = false;
        }
        char c = scancodeToChar(e.key.keysym.scancode, (SDL_Keymod) e.key.keysym.mod);
        if(c) currentText += c;
    }
}
