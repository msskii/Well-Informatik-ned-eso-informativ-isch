//
//  ItemSlot.cpp
//  Informatik
//
//  Created by Aaron Hodel on 08.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "ItemSlot.hpp"
#include "Inventory.hpp"

ItemSlot::ItemSlot(InventoryElement element) : renderItem(element)
{
    x = (int) (element.numSlot % INV_WIDTH) * INV_GRID_SIZE + INV_START_X;
    y = (int) (element.numSlot / INV_WIDTH) * INV_GRID_SIZE + INV_START_Y;
    
    w = INV_GRID_SIZE;
    h = INV_GRID_SIZE;
}

void ItemSlot::render(SDL_Renderer *renderer)
{
    SDL_Rect bck = {x + INV_GRID_BORDER, y + INV_GRID_BORDER, INV_GRID_SIZE - INV_GRID_BORDER, INV_GRID_SIZE - INV_GRID_BORDER};
    COLOR(renderer, hoverOver ? 0xFFAAAAAA : 0xFFFFFFFF);
    SDL_RenderFillRect(renderer, &bck);
    
    if(renderItem.item == nullptr || this == ((Inventory*) menu)->selected) return;

    SDL_Rect dst = {x, y, INV_GRID_SIZE, INV_GRID_SIZE};
    SDL_RenderCopy(renderer, renderItem.item->texture, NULL, &dst);
    
    if(texture.texture == nullptr || needsUpdate)
    {
        drawTextAspect(renderer, std::to_string(renderItem.amountItems).c_str(), 0xFF000000, x + INV_GRID_BORDER, y + INV_GRID_BORDER, INV_GRID_SIZE - INV_GRID_BORDER, INV_GRID_SIZE - INV_GRID_BORDER, texture);
        needsUpdate = false;
    }
    else
    {
        SDL_Rect r = {x + INV_GRID_BORDER, y + INV_GRID_BORDER, texture.textwidth, texture.textheight};
        SDL_RenderCopy(renderer, texture.texture, NULL, &r);
    }
}

void ItemSlot::processEvent(Menu *menu, SDL_Event e)
{
    Inventory* inv = (Inventory*) menu;
    
    if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
    {
        int xpos = (float) e.button.x / SCALE_X;
        int ypos = (float) e.button.y / SCALE_Y;

        if(this == inv->selected)
        {
            inv->hoverX = xpos;
            inv->hoverY = ypos;
        }
        hoverOver = xpos >= x && xpos <= x + w && ypos >= y && ypos <= y + h;
    }
    
    if(hoverOver && e.type == SDL_MOUSEBUTTONDOWN)
    {
        if(inv->selected == nullptr)
        {
            needsUpdate = true;
            
            inv->selected = renderItem.item == nullptr ? nullptr : this;
            inv->player->playerItems[renderItem.numSlot] = {nullptr, renderItem.numSlot, 0}; // Clear slot
            
            inv->hoverX = (float) e.button.x / SCALE_X;
            inv->hoverY = (float) e.button.y / SCALE_Y;
            
            consumeEvent = inv->selected != nullptr;
            return;
        }
    }
    
    if(inv->selected == this && e.type == SDL_MOUSEBUTTONDOWN)
    {
        // Place down item...
        needsUpdate = true;
        
        // calculate slot number
        int xpos = (float) e.button.x / SCALE_X;
        int ypos = (float) e.button.y / SCALE_Y;
        
        int xslot = (xpos - INV_START_X) / INV_GRID_SIZE;
        int yslot = (ypos - INV_START_Y) / INV_GRID_SIZE;
        
        if(xslot < 0 || yslot < 0 || xslot >= INV_WIDTH || yslot >= INV_HEIGHT) return; // Clicked outside of inventory
        
        int slotnum = xslot + yslot * INV_WIDTH;
        int oldslot = renderItem.numSlot;
        // Swapping slotnum with oldslot
        
        // Create copies of elements & update slot numbers
        InventoryElement newElementTo = renderItem; // Same as inv->player->playerItems[oldslot];
        newElementTo.numSlot = slotnum;
        InventoryElement newElementFrom = inv->player->playerItems[slotnum];
        newElementFrom.numSlot = oldslot;
        
        // Place in inventory
        inv->player->playerItems[slotnum] = newElementTo;
        inv->player->playerItems[oldslot] = newElementFrom;
        
        // Update slots
        renderItem = newElementFrom; // This slot is from, so we now hold the item from slotnum (The other slot)
        inv->slots[slotnum]->renderItem = newElementTo;
        
        // Pick up the other slots contents if there is an item & not the same slot to place it down
        inv->selected = newElementFrom.item == nullptr || oldslot == slotnum ? nullptr : inv->slots[oldslot];
        
        consumeEvent = true;
    }
}
