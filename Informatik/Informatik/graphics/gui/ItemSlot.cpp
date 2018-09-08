//
//  ItemSlot.cpp
//  Informatik
//
//  Created by Aaron Hodel on 08.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "ItemSlot.hpp"

ItemSlot::ItemSlot(int xpos, int ypos, Item *item) : renderItem(item)
{
    x = xpos * INV_GRID_SIZE + INV_START_X;
    y = ypos * INV_GRID_SIZE + INV_START_Y;
    
    w = INV_GRID_SIZE;
    h = INV_GRID_SIZE;
}

void ItemSlot::render(SDL_Renderer *renderer)
{
    
    SDL_Rect bck = {x + INV_GRID_BORDER, y + INV_GRID_BORDER, INV_GRID_SIZE - INV_GRID_BORDER, INV_GRID_SIZE - INV_GRID_BORDER};
    COLOR(renderer, hoverOver ? 0xFFAAAAAA : 0xFFFFFFFF);
    SDL_RenderFillRect(renderer, &bck);
    
    if(renderItem == nullptr) return;

    SDL_Rect dst = {x, y, INV_GRID_SIZE, INV_GRID_SIZE};
    SDL_RenderCopy(renderer, renderItem->texture, NULL, &dst);
}

void ItemSlot::processEvent(Menu *menu, SDL_Event e)
{
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
    {
        int xpos = (float) e.button.x / SCALE_X;
        int ypos = (float) e.button.y / SCALE_Y;
        hoverOver = xpos >= x && xpos <= x + w && ypos >= y && ypos <= y + h;
    }
}
