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
    
    selectionStart = (int) strlen(defaultText);
    currentIndex = selectionStart;
}

void TextBox::render()
{
    SDL_Rect dst = {x, y, w, h};
    // SDL_RenderCopy(renderer, textures[TEXTBOX], NULL, &dst);
    renderWithoutShading(gl_textures[TEXTBOX], {}, dst);
    
    usedScale = drawTextAspect(currentText.c_str(), 0xFF000000, dst, lastTexture, changed);
    changed = false;
    
    // cursor is after last character --> measure string till
    int tw, th;
    TTF_SizeText(font, currentText.substr(0, currentIndex).c_str(), &tw, &th);
    int realWidth = (int)((float) tw * usedScale);
    TTF_SizeText(font, currentText.substr(0, selectionStart).c_str(), &tw, &th);
    int selectionWidth = (int)((float) tw * usedScale);
    
    SDL_Rect selection;
    if(selectionStart < currentIndex) selection = {x + selectionWidth, y, realWidth - selectionWidth, h};
    else selection = {x + realWidth, y, selectionWidth - realWidth, h};
    fillRect(0xAF00FFFF, selection);
    
    if(!focus)
    {
        selectionStart = currentIndex;
        return;
    }
    
    SDL_Rect r = {x + realWidth, y, (int)(5.0 / SCALE_X), h};
    fillRect(0xFF000000, r);
}

void TextBox::processEvent(Menu *menu, SDL_Event e)
{
    if(e.type == SDL_MOUSEMOTION)
    {
        hoverOver = menu->active && e.button.x / SCALE_X >= x && e.button.x / SCALE_X <= x + w && e.button.y / SCALE_Y >= y && e.button.y / SCALE_Y <= y + h;
        
        if(!focus) return; // Dont track if we're not focused
        
        if(e.button.button == SDL_BUTTON_LEFT)
        {
            float xpos = e.button.x / SCALE_X - x;
            for(int i = (int) currentText.size(); i > 0; --i)
            {
                int tw, th;
                TTF_SizeText(font, currentText.substr(0, i).c_str(), &tw, &th);
                int realWidth = (int)((float) tw * usedScale);
                
                if(xpos >= realWidth)
                {
                    currentIndex = (int) i;
                    return;
                }
            }
            
            currentIndex = 0; // Leftmost position
        }
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
                TTF_SizeText(font, currentText.substr(0, i).c_str(), &tw, &th);
                int realWidth = (int)((float) tw / usedScale);
                
                if(xpos >= realWidth)
                {
                    currentIndex = (int) i;
                    selectionStart = currentIndex;
                    return;
                }
            }
            
            selectionStart = 0;
            currentIndex = 0; // Leftmost position
        }
    }
    else if(e.type == SDL_KEYDOWN && focus)
    {
        // Special keys...
        if(e.key.keysym.sym == SDLK_RIGHT)
        {
            if(++currentIndex > (int) currentText.size()) --currentIndex;
            if(!(e.key.keysym.mod & KMOD_SHIFT)) selectionStart = currentIndex;
            return;
        }
        else if(e.key.keysym.sym == SDLK_LEFT)
        {
            if(--currentIndex < 0) ++currentIndex;
            if(!(e.key.keysym.mod & KMOD_SHIFT)) selectionStart = currentIndex;
            return;
        }
        
        //e.key.keysym.scancode
        if(defaultText) // Clear current text
        {
            currentText = "";
            currentIndex = 0;
            selectionStart = 0;
            defaultText = false;
        }
        char c = scancodeToChar(e.key.keysym.scancode, (SDL_Keymod) e.key.keysym.mod);
        
        changed = true; // update text
        
        if(currentIndex == selectionStart)
        {
            if(c && c != '\x08') currentText.insert(currentText.begin() + currentIndex++, c);
            else if(c == '\x08' && currentText.size() > 0 && currentIndex > 0) currentText.erase(currentText.begin() + --currentIndex);
        }
        else
        {
            // Delete all chars from selectionstart to currentindex
            if(currentIndex < selectionStart)
            {
                int a = currentIndex;
                currentIndex = selectionStart;
                selectionStart = a;
            }
            
            while(currentIndex != selectionStart) currentText.erase(currentText.begin() + --currentIndex);
            
            if(c && c != '\x08') currentText.insert(currentText.begin() + currentIndex++, c);
        }
        
        selectionStart = currentIndex;
    }
}
