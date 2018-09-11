//
//  Dropdown.cpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Dropdown.hpp"

DropDown::DropDown(int defaultSelected, int _x, int _y, int _w, int _h, int id) : currentID(defaultSelected)
{
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    elementID = id;
}

void DropDown::addOption(int index, const char *text)
{
    elements.push_back({index, text});
    
    if(currentID == index) currentSelected = (int) elements.size() - 1;
}

void DropDown::render(SDL_Renderer *renderer)
{
    if(expanded)
    {
        if(toTheSide)
        {
            SDL_Rect dst = {x, y, w, h};
            SDL_RenderCopy(renderer, textures[DROPDOWN], NULL, &dst);
            int xoffset = x >= GAME_WIDTH - w ? -w : w;

            if(cachedText.texture == nullptr) drawTextAspect(renderer, elements[currentSelected].text, 0xFF000000, x, y, w, h, cachedText);
            else
            {
                SDL_Rect r = {x, y, cachedText.textwidth, cachedText.textheight};
                SDL_RenderCopy(renderer, cachedText.texture, NULL, &r);
            }

            xoffset += 100 * SCALE_X;
            for(int i = 0; i < (int) elements.size(); i++)
            {
                SDL_Rect dst = {x + xoffset - (int)(100 * SCALE_X), y +  - ((int) elements.size() * h / 2) + h * elements[i].id, w, h};
                SDL_RenderCopy(renderer, i == currentlyOver ? textures[DROPDOWN_ELEMENT_HOVER] : textures[DROPDOWN_ELEMENT], NULL, &dst);
                
                if(elements[i].cachedTexture.texture == nullptr) drawTextAspect(renderer, elements[i].text, 0xFF000000, x + xoffset, y - ((int) elements.size() * h / 2) + h * elements[i].id, w, h, elements[i].cachedTexture);
                else
                {
                    SDL_Rect r = {x + xoffset, y - ((int) elements.size() * h / 2) + h * elements[i].id, elements[i].cachedTexture.textwidth, elements[i].cachedTexture.textheight};
                    SDL_RenderCopy(renderer, elements[i].cachedTexture.texture, NULL, &r);
                }
            }
        }
        else
        {
            for(int i = 0; i < (int) elements.size(); i++)
            {
                SDL_Rect dst = {x, y + h * elements[i].id, w, h};
                SDL_RenderCopy(renderer, i == currentlyOver ? textures[DROPDOWN_ELEMENT_HOVER] : textures[DROPDOWN_ELEMENT], NULL, &dst);
                
                if(elements[i].cachedTexture.texture == nullptr) drawTextAspect(renderer, elements[i].text, 0xFF000000, x + (100 * SCALE_X), y + h * elements[i].id, w, h, elements[i].cachedTexture);
                else
                {
                    SDL_Rect r = {x + (int) (100 * SCALE_X), y + h * elements[i].id, elements[i].cachedTexture.textwidth, elements[i].cachedTexture.textheight};
                    SDL_RenderCopy(renderer, elements[i].cachedTexture.texture, NULL, &r);
                }
            }
        }
    }
    else
    {
        SDL_Rect dst = {x, y, w, h};
        SDL_RenderCopy(renderer, textures[DROPDOWN], NULL, &dst);
        
        if(cachedText.texture == nullptr) drawTextAspect(renderer, elements[currentSelected].text, 0xFF000000, x, y, w, h, cachedText);
        else
        {
            SDL_Rect r = {x, y, cachedText.textwidth, cachedText.textheight};
            SDL_RenderCopy(renderer, cachedText.texture, NULL, &r);
        }
    }
}

void DropDown::processEvent(Menu *menu, SDL_Event e)
{
    if(expanded)
    {
        int bx = (int)(e.button.x / SCALE_X);
        int by = (int)(e.button.y / SCALE_Y);
        if(toTheSide)
        {
            int xoffset = x >= GAME_WIDTH - w ? -w : w;
            bx -= xoffset;
            by += ((int) elements.size() * h / 2);
        }
        
        if(bx >= x && bx <= x + w && by >= y && by <= y + h * (int) elements.size())
        {
            int eid = (by - y) / h;
            for(int i = 0; i < (int) elements.size(); i++) if(eid == elements[i].id) currentlyOver = i;
        }
        
    }
    
    if(expanded)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
			int bx = (int)(e.button.x / SCALE_X);
			int by = (int)(e.button.y / SCALE_Y);
            
            // bx += w;
            if(toTheSide)
            {
                bx += x >= GAME_WIDTH - w ? w : -w;
                by += ((int) elements.size() * h / 2);
            }
            
            if(bx >= x && bx <= x + w && by >= y && by <= y + h * (int) elements.size())
            {
                // Select the one under the cursor
                int eid = (by - y) / h;
                currentID = eid;
                for(int i = 0; i < (int) elements.size(); i++) if(eid == elements[i].id) currentSelected = i;
                consumeEvent = true;
                expanded = false;
                
                if(clbck != nullptr) clbck(menu, elements[currentSelected]);
            }
            else
            {
                expanded = false;
            }
            
            SDL_DestroyTexture(cachedText.texture);
            cachedText.texture = nullptr;
        }
    }
    else
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            bool isOver = e.button.x / SCALE_X >= x && e.button.x / SCALE_X <= x + w && e.button.y / SCALE_Y >= y && e.button.y / SCALE_Y <= y + h;
            if(isOver)
            {
                consumeEvent = true;
                expanded = true;
            }
        }
    }
}
