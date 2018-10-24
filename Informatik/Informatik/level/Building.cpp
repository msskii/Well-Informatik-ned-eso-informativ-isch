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
            data.hitboxX = (float) data.xcoord + 1.0f;
            data.hitboxY = data.ycoord + 2.0f;
            

            data.hitboxXBehind = data.xcoord - 1.0f;
            data.hitboxYBehind = data.ycoord - 2.0f;
            data.hitboxsizeXBehind = 10.0f;
            data.hitboxsizeYBehind = 6.0f;
            
            break;
            
        case 1:
            //The Tavern
            building_surface = IMG_Load(GET_TEXTURE_PATH("buildings/Building_Tavern"));
            data.sizeX = 12;
            data.sizeY = 9;
            data.hitboxsizeX = 8;
            data.hitboxsizeY = 5;
            data.hitboxX = (float) data.xcoord + 2.0f;
            data.hitboxY = data.ycoord + 4.0f;
            
            
            data.hitboxXBehind = data.xcoord - 1.0f;
            data.hitboxYBehind = data.ycoord - 2.0f;
            data.hitboxsizeXBehind = 12.0f;
            data.hitboxsizeYBehind = 8.0f;
            
            break;
        case 2:
            //The Blacksmith
            building_surface = IMG_Load(GET_TEXTURE_PATH("buildings/Building_Blacksmith"));
            data.sizeX = 10;
            data.sizeY = 7;
            data.hitboxsizeX = 9;
            data.hitboxsizeY = 2;
            data.hitboxX = (float) data.xcoord + 1.0f;
            data.hitboxY = data.ycoord + 5.0f;
            
            
            data.hitboxXBehind = data.xcoord - 1.0f;
            data.hitboxYBehind = data.ycoord - 1.0f;
            data.hitboxsizeXBehind = 12.0f;
            data.hitboxsizeYBehind = 8.0f;
            
            break;
        default:
            break;
    }
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
    if(texture.id == 0) texture = getTexture(building_surface);
    
    SDL_Rect src = {0, 0, data.sizeX * TILE_SIZE / 2, data.sizeY * TILE_SIZE / 2};
    SDL_Rect dst = {(data.xcoord) * TILE_SIZE + xoffset, (data.ycoord) * TILE_SIZE + yoffset, data.sizeX * TILE_SIZE, data.sizeY * TILE_SIZE};
    
    if(dst.x >= (GAME_WIDTH + data.sizeX * TILE_SIZE) || dst.x < (-TILE_SIZE - data.sizeX * TILE_SIZE) || dst.y >= (GAME_HEIGHT + data.sizeY * TILE_SIZE) || dst.y < (-TILE_SIZE - data.sizeY * TILE_SIZE)) return; // Only render the visible ones...
    switch (data.buildingNumber) {
        case 0:
            if(level != nullptr && level->window != nullptr)
            {
                level->window->lights.addLight((float) dst.x + 40.0f, (float) dst.y + 210.0f, 10.0f, 0xFF000000, 1.0f, 0.0f);
                level->window->lights.addLight((float) dst.x + 40.0f, (float) dst.y + 206.0f, 20.0f, 0xFFFFFF00, 0.2f, 1.0f);
            }
            break;
        case 1:
            if(level != nullptr && level->window != nullptr)
            {
                level->window->lights.addLight((float) dst.x + (1.15f * 64.0f), (float) dst.y + (5.8f * 64.0f), 10.0f, 0xFF000000, 1.0f, 0.0f);
                level->window->lights.addLight((float) dst.x + (1.15f * 64.0f), (float) dst.y + (5.8f * 64.0f), 20.0f, 0xFFFFFF00, 0.2f, 1.0f);
            }
            break;
        case 2:
            if(level != nullptr && level->window != nullptr)
            {
                level->window->lights.addLight((float) dst.x + (8.7f * 64.0f), (float) dst.y + (5.45f * 64.0f), 10.0f, 0xFF000000, 1.0f, 0.0f);
                level->window->lights.addLight((float) dst.x + (8.7f * 64.0f), (float) dst.y + (5.45f * 64.0f), 200.0f, 0xFFFFFF00, 0.2f, 1.0f);
            }
            break;
            
            
        default:
            break;
    }
    
    
    renderWithShading(texture, src, dst);
}
