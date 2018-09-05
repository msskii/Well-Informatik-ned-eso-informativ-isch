//
//  EntityItem.cpp
//  Informatik
//
//  Created by Aaron Hodel on 05.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "EntityItem.hpp"

EntityItem::EntityItem()
{
    data.x_pos = TILE_SIZE * 4;
}

void EntityItem::onAddToLevel(Level *level) {}
void EntityItem::render(SDL_Renderer *renderer, int xoff, int yoff)
{
    COLOR(renderer, 0xFFFF00FF);
    SDL_Rect r = getBoundingBox();
    TRANSFORM_LEVEL_POS(r, xoff, yoff);
    SDL_RenderFillRect(renderer, &r);
}

void EntityItem::update(const uint8_t *keys) {}

void EntityItem::pickUp()
{
    
}
