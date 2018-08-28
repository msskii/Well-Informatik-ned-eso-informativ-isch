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
    Tile_surface = IMG_Load((TEXTURE_PATH + "sandy_ground.png").c_str());
}

Tile::Tile(int x, int y) : xcoord(x), ycoord(y)
{
    Tile_surface = IMG_Load((TEXTURE_PATH + "Tile_Stoneroadongrass.png").c_str());
}

void Tile::render(SDL_Renderer *renderer, int xoffset, int yoffset)
{
    /*SDL_Rect r = {xcoord * TILE_SIZE + xoffset, ycoord * TILE_SIZE + yoffset, TILE_SIZE, TILE_SIZE};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF - data.tileZ * 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderDrawRect(renderer, &r);*/
    
    if(texture == nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, Tile_surface);
        return;
    }
    
    SDL_Rect src = {0,0, 32, 32};
    SDL_Rect dst = {xcoord * TILE_SIZE + xoffset, ycoord * TILE_SIZE + yoffset, TILE_SIZE, TILE_SIZE};
    SDL_RenderCopy(renderer, texture, &src, &dst);
}
