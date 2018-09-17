//
//  Building.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 11.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Building.hpp"


Building::Building(int x, int y, uint16_t buildingNumber): data({buildingNumber, 0, 0, x, y})
{
    switch (buildingNumber) {
        case 0:
            //Old Mans Hut
            building_surface = IMG_Load(GET_TEXTURE_PATH("buildings/Building_OldManHut"));
            data.sizeX = 6;
            data.sizeY = 5;
            data.hitboxsizeX = 6;
            data.hitboxsizeY = 3;
            data.hitboxX = xcoord;
            data.hitboxY = ycoord + 1.5;
            
            data.hitboxXBehind = xcoord - 1;
            data.hitboxYBehind = ycoord - 1;
            data.hitboxsizeXBehind = 8;
            data.hitboxsizeYBehind = 5.4;

            
            
            break;
            
        default:
            break;
            
            
    }
}

Building::Building(BuildingData d) : data(d)
{
    switch (data.buildingNumber) {
        case 0:
            //Old Mans Hut
            building_surface = IMG_Load(GET_TEXTURE_PATH("buildings/Building_OldManHut"));
            data.sizeX = 6;
            data.sizeY = 5;
            break;
            
        default:
            break;
            
            
    }}

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

void Building::render(SDL_Renderer *renderer, int xoffset, int yoffset)
{
    if (texture == nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, building_surface);
    }
    
    SDL_Rect src = {0, 0, data.sizeX * TILE_SIZE / 2, data.sizeY * TILE_SIZE / 2}; // For individual 32 by 32 tiles
    SDL_Rect dst = {data.xcoord * TILE_SIZE + xoffset, data.ycoord * TILE_SIZE + yoffset, data.sizeX * TILE_SIZE, data.sizeY * TILE_SIZE};
    
    if(dst.x >= GAME_WIDTH || dst.x < -TILE_SIZE || dst.y >= GAME_HEIGHT || dst.y < -TILE_SIZE) return; // Only render the visible ones...
    SDL_RenderCopy(renderer, texture, &src, &dst);
}
