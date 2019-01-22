//
//  Entity.cpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Entity.hpp"
#include "../level/Level.hpp"

void Entity::addedToLevel(Level *l)
{
    level = l;
    onAddToLevel(l);
    
    //printf("[DEBUG] Entity name is: %s\n", typeid(*this).name());
}

Entity::~Entity()
{
    
}

bool Entity::isInside(float dx, float dy)
{
    if(data.x_pos + dx < 0 || data.x_pos + dx >= TILE_SIZE * 50 || data.y_pos + dy < 0 || data.y_pos + dy >= TILE_SIZE * 50) return true; // Out of bounds = you cant walk
    for(int point_index = 0; point_index < 4; point_index++)
    {
        float x_offset = dx + (data.width) * (point_index % 2);
        float y_offset = dy + (data.height) * (int)(point_index / 2);
        
        if(level->getTile((int)((data.x_pos + x_offset) / TILE_SIZE), (int)((data.y_pos + y_offset) / TILE_SIZE)).data.tileZ != data.z_pos) return true;
        if(level->getBuildingCollision(data.x_pos + x_offset, data.y_pos + y_offset)) return true;
    }

    
    return false;
}

bool Entity::isInsideEntity(float x, float y)
{
    return (data.x_pos < x && data.x_pos + data.width > x && data.y_pos < y && data.y_pos + data.width > y);
}

void Entity::correctMovement(float &dx, float &dy)
{
    if(isInside(dx, dy))
    {
        float xmax = STEP_ACCURACY, ymax = STEP_ACCURACY;
        
        if(dx != 0) for(xmax = 1; xmax <= STEP_ACCURACY; xmax++) if(isInside(dx * xmax / STEP_ACCURACY, dy)) break;
        --xmax; // Not up to and with (inside), just up to the thing
        
        if(dy != 0) for(ymax = 1; ymax <= STEP_ACCURACY; ymax++) if(isInside(dx * xmax / STEP_ACCURACY, dy * ymax / STEP_ACCURACY)) break;
        --ymax; // Not up to and with (inside), just up to the thing
        
        // Check x again
        if(dx != 0) for(xmax = 1; xmax <= STEP_ACCURACY; xmax++) if(isInside(dx * xmax / STEP_ACCURACY, dy * ymax / STEP_ACCURACY)) break;
        --xmax;
        
        if(xmax < 0) xmax = 0;
        if(ymax < 0) ymax = 0;
        
        dx *= xmax / STEP_ACCURACY;
        dy *= ymax / STEP_ACCURACY;
    }
}

bool Entity::collision(float x, float y)
{
    return false;
}

uint32_t Entity::getEntitySize()
{
    return sizeof(EntityData);
}

uint8_t* Entity::getSerializedEntity(uint8_t *buffer)
{
    Multiplayer::write<EntityData>(buffer, data);
    return buffer;
}

