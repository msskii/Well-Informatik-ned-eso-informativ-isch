//
//  Tile.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Tile.hpp"

Tile::Tile() : xcoord(0), ycoord(0)
{
    Tile_surface = IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/sandy_ground.png"));
    brightness_modifier = (rand() % 1 == 0 ? -1 : 1) * rand() % 0x2F;
}

Tile::Tile(int x, int y) : xcoord(x), ycoord(y)
{
    Tile_surface = IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass.png"));
    brightness_modifier = (rand() % 1 == 0 ? -1 : 1) * rand() % 0x2F;
}

void Tile::render(SDL_Renderer *renderer, int xoffset, int yoffset)
{
    if(texture == nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, Tile_surface);
        return;
    }
    
    SDL_Rect src = {0, 0, 32, 32}; // For individual 32 by 32 tiles
    SDL_Rect dst = {xcoord * TILE_SIZE + xoffset, ycoord * TILE_SIZE + yoffset, TILE_SIZE, TILE_SIZE};
    SDL_RenderCopy(renderer, texture, &src, &dst);
    
    if(brightness_modifier > 0)
    {
        COLOR(renderer, (brightness_modifier << 24) | 0xFFFFFF); // brightness modifier = 0 -> nothing changed, = 0xFF -> full white
    }
    else
    {
        COLOR(renderer, (-brightness_modifier << 24) | 0x000000); // brightness modifier = 0 -> nothing changed, = 0xFF -> full black
    }
    SDL_RenderFillRect(renderer, &dst); // Render over the tile
    
    if(data.tileZ)
    {
        
    }
}
