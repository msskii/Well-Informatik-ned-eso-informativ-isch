//
//  Inventory.cpp
//  Informatik
//
//  Created by Aaron Hodel on 06.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Inventory.hpp"

Inventory::Inventory(Player *p)
{
    background_surface = IMG_Load(GET_TEXTURE_PATH("/test"));
}

bool Inventory::shouldWindowClose() { return false; }
void Inventory::renderMenu(SDL_Renderer *renderer)
{
    /*COLOR(renderer, 0xAFFF00FF);
    SDL_Rect r = {0, 0, GAME_WIDTH, GAME_HEIGHT};
    SDL_RenderFillRect(renderer, &r);*/
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
