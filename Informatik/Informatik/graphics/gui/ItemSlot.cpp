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
    if(element.item != nullptr) printf("Item in slot nr. %d\n", element.numSlot);
    
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
    
    drawTextAspect(renderer, std::to_string(renderItem.amountItems).c_str(), 0xFF000000, x + INV_GRID_BORDER, y + INV_GRID_BORDER, INV_GRID_SIZE - INV_GRID_BORDER, INV_GRID_SIZE - INV_GRID_BORDER);
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
            printf("Picked up item in slot: %d\n", renderItem.numSlot);
            inv->selected = renderItem.item == nullptr ? nullptr : this;
            inv->hoverX = (float) e.button.x / SCALE_X;
            inv->hoverY = (float) e.button.y / SCALE_Y;
            return;
        }
    }
    
    if(inv->selected == this && e.type == SDL_MOUSEBUTTONDOWN)
    {
        // Place down item...
        
        // calculate slot number
        int xpos = (float) e.button.x / SCALE_X;
        int ypos = (float) e.button.y / SCALE_Y;
        
        int xslot = (xpos - INV_START_X) / INV_GRID_SIZE;
        int yslot = (ypos - INV_START_Y) / INV_GRID_SIZE;
        
        if(xslot < 0 || yslot < 0 || xslot >= INV_WIDTH || yslot >= INV_HEIGHT) return; // Clicked outside of inventory
        
        int slotnum = xslot + yslot * INV_WIDTH;
        
        if(inv->player->playerItems[slotnum].item != nullptr)
        {
            printf("Already an item in slot number: %d: %p\n", slotnum, inv->player->playerItems[slotnum].item);
            
            InventoryElement nelement = inv->player->playerItems[slotnum];
            nelement.numSlot = renderItem.numSlot;
            inv->player->playerItems[slotnum] = renderItem;
            inv->player->playerItems[renderItem.numSlot] = nelement;
            
            for(int i = 0; i < (int) inv->elements.size(); i++)
            {
                if(((ItemSlot*) inv->elements[i])->renderItem.numSlot == slotnum)
                {
                    ((ItemSlot*) inv->elements[i])->renderItem = renderItem;
                    inv->selected = (ItemSlot*) inv->elements[i];
                    break;
                }
            }
            
            renderItem = nelement;
            inv->player->playerItems[slotnum].numSlot = slotnum; // Change to new slot number
        }
        else
        {
            printf("Placing down item in slot: %d\n", slotnum);
            inv->player->playerItems[slotnum] = renderItem;
            InventoryElement nelement = {nullptr, renderItem.numSlot, 0};
            inv->player->playerItems[renderItem.numSlot] = nelement;
            
            for(int i = 0; i < (int) inv->elements.size(); i++)
            {
                if(((ItemSlot*) inv->elements[i])->renderItem.numSlot == slotnum) ((ItemSlot*) inv->elements[i])->renderItem = renderItem;
            }
            
            renderItem = nelement;
            inv->player->playerItems[slotnum].numSlot = slotnum; // Change to new slot number
            inv->selected = nullptr;
        }
    }
}
