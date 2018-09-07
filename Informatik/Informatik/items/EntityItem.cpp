//
//  EntityItem.cpp
//  Informatik
//
//  Created by Aaron Hodel on 05.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "EntityItem.hpp"
#include "../level/Level.hpp"

EntityItem::EntityItem(int x, int y, Item *i) : item(i)
{
    data.x_pos = TILE_SIZE * x;
    data.y_pos = TILE_SIZE * y;
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
    level->player->playerItems.push_back(item);
}
