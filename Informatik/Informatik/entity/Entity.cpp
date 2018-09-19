//
//  Entity.cpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Entity.hpp"
#include "Level.hpp"

void Entity::addedToLevel(Level *l)
{
    level = l;
    onAddToLevel(l);
}

Entity::~Entity()
{
    
}

bool Entity::isInside(float dx, float dy)
{
    if(data.x_pos + dx < 0 || data.x_pos + dx >= TILE_SIZE * 50 || data.y_pos + dy < 0 || data.y_pos + dy >= TILE_SIZE * 50) return true; // Out of bounds = you cant walk
    for(int point_index = 0; point_index < 4; point_index++)
    {
        float player_x_offset = dx + (PLAYER_WIDTH) * (point_index % 2);
        float player_y_offset = dy + (PLAYER_HEIGHT) * (int)(point_index / 2);
        
        if(level->getTile((int)((data.x_pos + player_x_offset) / TILE_SIZE), (int)((data.y_pos + player_y_offset) / TILE_SIZE)).data.tileZ != data.z_pos) return true;
        if(level->getBuildingCollision(data.x_pos + player_x_offset, data.y_pos + player_y_offset)) return true;
    }

    
    return false;
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

