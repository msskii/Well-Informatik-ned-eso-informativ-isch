//
//  TextBox.cpp
//  Informatik
//
//  Created by Aaron Hodel on 24.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "TextBox.hpp"
#include "../Menu.hpp"

TextBox::TextBox(const char *defaultText, int _x, int _y, int _w, int _h, int id) : currentText(std::string(defaultText))
{
    x = _x;
    y = _y;
    w = _w;
    h = _h;
	elementID = id;
}

void TextBox::render(SDL_Renderer *renderer)
{
    usedScale = drawTextAspect(renderer, currentText.c_str(), 0xFF000000, x, y, w, h);
    
    // cursor is after last character --> measure string till
    int tw, th;
    TTF_SizeText(font, currentText.substr(0, currentIndex).c_str(), &tw, &th);
    int realWidth = (int)((float) tw / SCALE_X * usedScale);
    
    COLOR(renderer, 0xFF000000);
    SDL_Rect r = {x + realWidth, y, (int)(5.0 / SCALE_X), h};
    SDL_RenderFillRect(renderer, &r);
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
        
        if(hoverOver)
        {
            float xpos = e.button.x / SCALE_X - x;
            for(int i = (int) currentText.size(); i > 0; --i)
            {
                int tw, th;
                TTF_SizeText(font, currentText.substr(0, i - 1).c_str(), &tw, &th);
                int realWidth = (int)((float) tw / SCALE_X * usedScale);
                
                if(xpos >= realWidth)
                {
                    currentIndex = (int) i;
                    return;
                }
            }
            
            currentIndex = 0; // Leftmost position
        }
    }
    else if(e.type == SDL_KEYDOWN && focus)
    {
        // Special keys...
        if(e.key.keysym.sym == SDLK_RIGHT)
        {
            if(++currentIndex > currentText.size()) --currentIndex;
            return;
        }
        else if(e.key.keysym.sym == SDLK_LEFT)
        {
            if(--currentIndex < 0) ++currentIndex;
            return;
        }
        
        //e.key.keysym.scancode
        if(defaultText) // Clear current text
        {
            currentText = "";
            currentIndex = 0;
            defaultText = false;
        }
        char c = scancodeToChar(e.key.keysym.scancode, (SDL_Keymod) e.key.keysym.mod);
        if(c && c != '\x08') currentText.insert(currentText.begin() + currentIndex++, c);
        else if(c == '\x08' && currentText.size() > 0) currentText.erase(currentText.begin() + --currentIndex);
    }
}
