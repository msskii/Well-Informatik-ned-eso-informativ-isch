//
//  Inventory.cpp
//  Informatik
//
//  Created by Aaron Hodel on 06.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Inventory.hpp"

#define X_START_POS (270)
#define Y_START_POS (270)

// Where does the inventory with items start
#define INV_START_X (X_START_POS)
#define INV_START_Y (Y_START_POS + 90)

#define INV_GRID_SIZE 50 // The slots width
#define INV_GRID_BORDER 4 // The Border around the slots in pixels

#define INV_WIDTH 20
#define INV_HEIGHT 9

Inventory::Inventory(Player *p)
{
    background_surface = IMG_Load(GET_TEXTURE_PATH("/backgrounds/testback"));
}

bool Inventory::shouldWindowClose() { return false; }

void Inventory::renderMenu(SDL_Renderer *renderer)
{
    for(size_t i = 0; i < window->level->player->playerItems.size(); i++)
    {
        Item *item = window->level->player->playerItems[i];
        int xpos = INV_START_X + INV_GRID_SIZE * (i % INV_WIDTH);
        int ypos = INV_START_Y + INV_GRID_SIZE * (int) (i / INV_WIDTH);
        
        SDL_Rect dst = {xpos, ypos, INV_GRID_SIZE, INV_GRID_SIZE};
        SDL_RenderCopy(renderer, item->texture, NULL, &dst);
    }
}

void Inventory::updateMenu(const uint8_t *keys)
{
    if(keys[SDL_SCANCODE_RETURN])
    {
        close();
    }
}

void Inventory::onOpen() {}
void Inventory::onClose() { window->paused = false; } // Unpause game
