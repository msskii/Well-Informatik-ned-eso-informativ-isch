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
    data.x_pos = (float) TILE_SIZE * x;
    data.y_pos = (float) TILE_SIZE * y;
}

void EntityItem::onAddToLevel(Level *level) {}

void EntityItem::render(int xoff, int yoff)
{
    if(item == nullptr || item->surface == nullptr) return;
    if(item->texture.id == 0) item->texture = getTexture(item->surface);
    
    SDL_Rect r = getBoundingBox();
    TRANSFORM_LEVEL_POS(r, xoff, yoff);
    //SDL_RenderCopy(renderer, item->texture, NULL, &r);
    renderWithShading(item->texture, {}, r);
}

void EntityItem::update(const uint8_t *keys) {}

void EntityItem::pickUp()
{
    Player *player = level->getPlayer(data.x_pos, data.y_pos);
    for(int i = 0; i < INV_WIDTH * INV_HEIGHT; i++)
    {
        if(player->playerItems[i].item != nullptr && *item == player->playerItems[i].item)
        {
            player->playerItems[i].item = item;
            ++player->playerItems[i].amountItems; // Increase amount of items in that slot
            return;
        }
    }
    for(int i = 0; i < INV_WIDTH * INV_HEIGHT; i++)
    {
        if(player->playerItems[i].item == nullptr)
        {
            player->playerItems[i].item = item;
            ++player->playerItems[i].amountItems; // Increase amount of items in that slot
            return;
        }
    }
    printf("Couldnt pick up item. Inventory is full\n");
}

uint32_t EntityItem::getEntitySize()
{
    if(item == nullptr) return sizeof(EntityData) + 4 + 5;
    return sizeof(EntityData) + 4 + (int) strlen(item->name);
}

uint8_t *EntityItem::getSerializedEntity(uint8_t *buffer)
{
    Multiplayer::write<EntityData>(buffer, data);
    if(item == nullptr || item->name == nullptr)
    {
        Multiplayer::writeString(buffer, "test", 4);
    }
    else
    {
        Multiplayer::writeString(buffer, item->name, (int) strlen(item->name));
    }
    return buffer;
}
