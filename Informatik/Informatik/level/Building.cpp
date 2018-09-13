//
//  Building.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 11.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Building.hpp"


Building::Building(int x, int y, uint16_t buildingNumber): xcoord(x), ycoord(y), data({buildingNumber,0,0})
{
    switch (buildingNumber) {
        case 0:
            //Old Mans Hut
            building_surface = IMG_Load(GET_TEXTURE_PATH("buildings/Building_OldManHut"));
            data.sizeX = 6;
            data.sizeY = 5;
            break;
            
        default:
            break;
            
            
    }
    
}
Building::Building()
{
    
}

bool Building::isInside(float x, float y)
{
    if((xcoord * TILE_SIZE < x && (xcoord * TILE_SIZE + data.sizeX * TILE_SIZE) > x) && (ycoord * TILE_SIZE < y && (ycoord *TILE_SIZE + data.sizeY * TILE_SIZE) > y))
    {
       return true;
    }
    
    return false;
}


void Building::render(SDL_Renderer *renderer, int xoffset, int yoffset)
{
<<<<<<< HEAD
    if (texture == nullptr) {
=======
    if (texture == nullptr)
    {
>>>>>>> 99f54219a51e0fdad6830cf5b3efbb2af38e7747
        texture = SDL_CreateTextureFromSurface(renderer, building_surface);
    }
    
    SDL_Rect src = {0, 0, data.sizeX * TILE_SIZE / 2, data.sizeY * TILE_SIZE / 2}; // For individual 32 by 32 tiles
    SDL_Rect dst = {xcoord * TILE_SIZE + xoffset, ycoord * TILE_SIZE + yoffset, data.sizeX * TILE_SIZE, data.sizeY * TILE_SIZE};
    
    if(dst.x >= GAME_WIDTH || dst.x < -TILE_SIZE || dst.y >= GAME_HEIGHT || dst.y < -TILE_SIZE) return; // Only render the visible ones...
    SDL_RenderCopy(renderer, texture, &src, &dst);
}
