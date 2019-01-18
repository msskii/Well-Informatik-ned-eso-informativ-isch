//
//  EntityItem.cpp
//  Informatik
//
//  Created by Aaron Hodel on 05.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "EntityItem.hpp"
#include "../level/Level.hpp"

#define GRAVITY 1.0f
#define DRAG 0.8f
#define CUT_OFF 2.0f

EntityItem::EntityItem(float x, float y, const char *id)
{
    initItem(x, y, id);
}

EntityItem::EntityItem(float x, float y, const char *id, float vx, float vy) : vx(vx), vy(vy), initY(y)
{
    initItem(x, y, id);
}


void EntityItem::onAddToLevel(Level *level) {}

void EntityItem::render(int xoff, int yoff)
{
    if(item == nullptr || item->surface == nullptr) return;
    if(item->texture.id == 0) item->texture = getTexture(item->surface);
    SDL_Rect src = {32 * anim, 0, 32, 32};
    SDL_Rect dst = getBoundingBox();
    TRANSFORM_LEVEL_POS(dst, xoff, yoff);
    renderWithShading(item->texture, src, dst);
    
    //fillRect(0xFFFF00FF, dst);
}

void EntityItem::update(const uint8_t *keys)
{
    //update movement
    if (vx != 0 || vy != 0 || data.y_pos < initY)
    {
        vy -= GRAVITY;
        data.x_pos += vx;
        data.y_pos -= vy;
        //Bounce if on the ground
        if (data.y_pos > initY && vy < 0)
        {
            vy = -vy * DRAG;
            vx *= DRAG;
            if (abs(vy) < CUT_OFF)
            {
                vx = 0;
                vy = 0;
            }
        }
        //bounce on walls
        int coordLeft = int(data.y_pos / TILE_SIZE) * level_width + (int)(data.x_pos / TILE_SIZE);
        int coordRight = int(data.y_pos / TILE_SIZE) * level_width + (int)((data.x_pos + data.width) / TILE_SIZE);
        if(level->tiles[coordLeft].data.tileNumber == TILE_EMPTY || level->tiles[coordRight].data.tileNumber == TILE_EMPTY)
        {
            vx *= -1;
        }
    }
    
    //animation
    if (data.animFrames)
    {
        if((timer++) >= data.animeSpeed)
        {
            timer = 0;
            anim = (anim + 1) % data.animFrames;
        }
    }
}

void EntityItem::pickUp()
{
    Player *player = level->getPlayer(data.x_pos, data.y_pos);
    
    if (ID == "mana_potion") {
        player->currentMana += 50;
    }
    else if (ID == "health_potion") {
        player->currentHealth += 20;
    }
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

void EntityItem::initItem(float x, float y, const char *id)
{
    data.x_pos = x;
    data.y_pos = y;
    item = new Item(id);
    ID = id;
    
    data.width = (float) item->texture_width;
    data.height = (float) item->texture_height;
    data.animeSpeed = item->animationSpeed;
    data.animFrames = item->animationFrames;
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
