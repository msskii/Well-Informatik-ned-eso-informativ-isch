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
    //texture = getTexture(background_surface);
    
    for(int i = 0; i < INV_WIDTH * INV_HEIGHT; i++)
    {
        slots.push_back((ItemSlot*) addElement(new ItemSlot(p->playerItems[i])));
    }
}

bool Inventory::shouldWindowClose() { return false; }

void Inventory::drawOverlay()
{
    if(selected == nullptr || selected->renderItem.item == nullptr) return; // No item selected
    
    SDL_Rect r = {hoverX, hoverY, INV_GRID_SIZE, INV_GRID_SIZE};
    renderWithoutShading(selected->renderItem.item->texture, {}, r);
}

void Inventory::renderMenu()
{
    // Set to white...
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Inventory::updateMenu(const uint8_t *keys)
{
    if(keys[SDL_SCANCODE_RETURN])
    {
        close();
    }
}

void Inventory::onOpen() {}
void Inventory::onClose()
{
    window->paused = false;
    if(selected != nullptr)
    {
        // Place selected item in correct spot
        player->playerItems[selected->renderItem.numSlot] = selected->renderItem;
    }
}
