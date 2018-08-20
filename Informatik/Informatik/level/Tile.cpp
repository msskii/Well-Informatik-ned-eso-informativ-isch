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
    
}

Tile::Tile(int x, int y) : xcoord(x), ycoord(y)
{
    
}

void Tile::render(SDL_Renderer *renderer, int xoffset, int yoffset)
{
    SDL_Rect r = {xcoord * TILE_SIZE + xoffset, ycoord * TILE_SIZE + yoffset, TILE_SIZE, TILE_SIZE};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderDrawRect(renderer, &r);
}
