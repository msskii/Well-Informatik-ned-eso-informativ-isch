//
//  Building.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 11.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Building.hpp"
#include "../level/Level.hpp"

Building::Building(int x, int y, uint16_t buildingNumber, Level *l): data({buildingNumber, 0, 0, x, y}), level(l)
{
    switch (buildingNumber)
    {
        case 0:
            //Old Mans Hut
            building_surface = IMG_Load(GET_TEXTURE_PATH("buildings/Building_OldManHut"));
            data.sizeX = 8;
            data.sizeY = 5;
            data.hitboxsizeX = 6;
            data.hitboxsizeY = 3;
            data.hitboxX = (float) data.xcoord;
            data.hitboxY = data.ycoord + 1.5f;
            

            data.hitboxXBehind = data.xcoord - 2.0f;
            data.hitboxYBehind = data.ycoord - 1.0f;
            data.hitboxsizeXBehind = 8.0f;
            data.hitboxsizeYBehind = 5.4f;
            data.textureOffsetX = -1;
            
            break;
            
        default:
            break;
    }
    texture = getTexture(building_surface);
}

Building::Building(BuildingData d, Level *l) : data(d), level(l)
{
    switch (data.buildingNumber)
    {
        case 0:
            //Old Mans Hut
            building_surface = IMG_Load(GET_TEXTURE_PATH("buildings/Building_OldManHut"));
            data.sizeX = 8;
            data.sizeY = 5;
            break;
            
        default:
            break;
    }
}

bool Building::isInside(float x, float y)
{
    if((data.hitboxX * TILE_SIZE < x && (data.hitboxX * TILE_SIZE + data.hitboxsizeX * TILE_SIZE) > x) && (data.hitboxY * TILE_SIZE < y && (data.hitboxY * TILE_SIZE + data.hitboxsizeY * TILE_SIZE) > y))
    {
        return true;
    }
    
    return false;
}

bool Building::isBehind(float x, float y)
{
    if((data.hitboxXBehind * TILE_SIZE < x && (data.hitboxXBehind * TILE_SIZE + data.hitboxsizeXBehind * TILE_SIZE) > x) && (data.hitboxYBehind * TILE_SIZE < y && (data.hitboxYBehind * TILE_SIZE + data.hitboxsizeYBehind * TILE_SIZE) > y))
    {
        return true;
    }
    return false;
}

void Building::render(int xoffset, int yoffset)
{
    SDL_Rect src = {0, 0, data.sizeX * TILE_SIZE / 2, data.sizeY * TILE_SIZE / 2}; // For individual 32 by 32 tiles
    SDL_Rect dst = {(data.xcoord + data.textureOffsetX) * TILE_SIZE + xoffset, (data.ycoord + data.textureOffsetY) * TILE_SIZE + yoffset, data.sizeX * TILE_SIZE, data.sizeY * TILE_SIZE};
    
    if(dst.x >= (GAME_WIDTH + data.sizeX * TILE_SIZE) || dst.x < (-TILE_SIZE - data.sizeX * TILE_SIZE) || dst.y >= (GAME_HEIGHT + data.sizeY * TILE_SIZE) || dst.y < (-TILE_SIZE - data.sizeY * TILE_SIZE)) return; // Only render the visible ones...
    if(level != nullptr) level->window->lights.addLight({(float) dst.x + 40.0f, (float) dst.y + 220.0f, 10.0f, 1, 1, 1});
    renderWithShading(texture, src, dst);
}
