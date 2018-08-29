//
//  Dropdown.cpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Dropdown.hpp"

DropDown::DropDown(int defaultSelected, int _x, int _y, int _w, int _h, int id) : currentID(defaultSelected), x(_x), y(_y), w(_w), h(_h)
{
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
        if(toTheRight)
        {
            drawTextAspect(renderer, elements[currentSelected].text, 0xFF000000, x, y, w, h);
            for(int i = 0; i < (int) elements.size(); i++)
            {
                drawTextAspect(renderer, elements[i].text, 0xFF000000, x + w, y - ((int) elements.size() * h / 2) + h * elements[i].id, w, h);
            }
        }
        else
        {
            for(int i = 0; i < (int) elements.size(); i++)
            {
                drawTextAspect(renderer, elements[i].text, 0xFF000000, x, y + h * elements[i].id, w, h);
            }
        }
    } else drawTextAspect(renderer, elements[currentSelected].text, 0xFF000000, x, y, w, h);
}

void DropDown::processEvent(Menu *menu, SDL_Event e)
{
    if(expanded)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            int bx = e.button.x / SCALE_X;
            int by = e.button.y / SCALE_Y;
            
            if(toTheRight)
            {
                bx += w;
                by += ((int) elements.size() * h / 2);
            }
            
            if(bx >= x && bx <= x + w && by >= y && by <= y + h * (int) elements.size())
            {
                expanded = false;
            }
            else
            {
                // Select the one under the cursor
                int eid = (by - y) / h;
                currentID = eid;
                for(int i = 0; i < (int) elements.size(); i++) if(eid == elements[i].id) currentSelected = i;
                consumeEvent = true;
                expanded = false;
            }
        }
    }
    else
    {
        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            bool isOver = e.button.x / SCALE_X >= x && e.button.x / SCALE_X <= x + w && e.button.y / SCALE_Y >= y && e.button.y / SCALE_Y <= y + h;
            if(isOver)
            {
                expanded = true;
            }
        }
    }
}
