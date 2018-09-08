//
//  EntityItem.cpp
//  Informatik
//
//  Created by Aaron Hodel on 05.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "EntityItem.hpp"
#include "../level/Level.hpp"

EntityItem::EntityItem(int x, int y, Item *i)
{
    data.x_pos = TILE_SIZE * x;
    data.y_pos = TILE_SIZE * y;
    
    item = i;
}

void EntityItem::onAddToLevel(Level *level) {}

void EntityItem::render(SDL_Renderer *renderer, int xoff, int yoff)
{
    SDL_Rect r = getBoundingBox();
    TRANSFORM_LEVEL_POS(r, xoff, yoff);
    SDL_RenderCopy(renderer, item->texture, NULL, &r);
}

void EntityItem::update(const uint8_t *keys) {}

void EntityItem::pickUp()
{
    for(int i = 0; i < INV_WIDTH * INV_HEIGHT; i++)
    {
        if(level->player->playerItems[i].item == nullptr || *item == level->player->playerItems[i].item)
        {
            level->player->playerItems[i].item = item;
            ++level->player->playerItems[i].amountItems; // Increase amount of items in that slot
            return;
        }
    }
}
