//
//  Inventory.cpp
//  Informatik
//
//  Created by Aaron Hodel on 06.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Inventory.hpp"

Inventory::Inventory(Player *p) : player(p)
{
    background_surface = IMG_Load(GET_TEXTURE_PATH("/backgrounds/testback"));
    
    for(int i = 0; i < INV_WIDTH * INV_HEIGHT; i++)
    {
        addElement(new ItemSlot(p->playerItems[i]));
    }
}

bool Inventory::shouldWindowClose() { return false; }

void Inventory::drawOverlay(SDL_Renderer *renderer)
{
    if(selected == nullptr || selected->renderItem.item == nullptr) return; // No item selected
    
    SDL_Rect r = {hoverX, hoverY, INV_GRID_SIZE, INV_GRID_SIZE};
    SDL_RenderCopy(renderer, selected->renderItem.item->texture, NULL, &r);
}

void Inventory::renderMenu(SDL_Renderer *renderer) {}

void Inventory::updateMenu(const uint8_t *keys)
{
    if(keys[SDL_SCANCODE_RETURN])
    {
        close();
    }
}

void Inventory::onOpen() {}
void Inventory::onClose() { window->paused = false; } // Unpause game
