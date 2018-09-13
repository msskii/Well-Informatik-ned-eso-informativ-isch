//
//  Building.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 11.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Building.hpp"


Building::Building(int x, int y, uint16_t buildingNumber): xcoord(x), ycoord(y), data({buildingNumber,0,0,(uint16_t)x,(uint16_t)y})
{
    printf("initial xcoord:%d\n", xcoord);
    switch (buildingNumber) {
        case 0:
            //Old Mans Hut
            building_surface = IMG_Load(GET_TEXTURE_PATH("buildings/Building_OldManHut"));
            data.sizeX = 6;
            data.sizeY = 5;
            break;
            
        default:
            building_surface = IMG_Load(GET_TEXTURE_PATH("buildings/Building_OldManHut"));
            data.sizeX = 6;
            data.sizeY = 5;
            break;
            
            
    }
    
}
Building::Building()
{
    
}

bool Building::isInside(float x, float y)
{
    if((20 * TILE_SIZE < x && (20 * TILE_SIZE + 7 * TILE_SIZE) > x) && (20 * TILE_SIZE < y && (20 *TILE_SIZE + 5 * TILE_SIZE) > y))
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
    SDL_Rect dst = {xcoord * TILE_SIZE + xoffset, ycoord * TILE_SIZE + yoffset, data.sizeX * TILE_SIZE, data.sizeY * TILE_SIZE};
    
    if(dst.x >= GAME_WIDTH || dst.x < -TILE_SIZE || dst.y >= GAME_HEIGHT || dst.y < -TILE_SIZE) return; // Only render the visible ones...
    SDL_RenderCopy(renderer, texture, &src, &dst);
}
