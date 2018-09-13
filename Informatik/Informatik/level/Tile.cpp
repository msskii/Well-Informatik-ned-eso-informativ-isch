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

Tile::Tile(int x, int y, uint16_t tileNumber) : xcoord(x), ycoord(y), data({ tileNumber, 0})
{
    
}

Tile::Tile(int x, int y, uint16_t tileNumber, uint8_t zheight) : xcoord(x), ycoord(y), data({ tileNumber, zheight})
{
    //Tile_surface = loadTileVariant(tileNumber, data.variant); // Since reloadTexture is called anyway, theres no need to initialize this here is there?
}

void Tile::reloadTexture(SDL_Renderer *renderer)
{
    SDL_DestroyTexture(texture); // clear texture & mark as garbage
    SDL_FreeSurface(Tile_surface);
    
    Tile_surface = loadTileVariant(data.tileNumber, data.variant);
    texture = SDL_CreateTextureFromSurface(renderer, Tile_surface);
}

void Tile::render(SDL_Renderer *renderer, int xoffset, int yoffset)
{
    SDL_Rect src = {0, 0, 32, 32}; // For individual 32 by 32 tiles
    SDL_Rect dst = {xcoord * TILE_SIZE + xoffset, ycoord * TILE_SIZE + yoffset, TILE_SIZE, TILE_SIZE};
   
    if(dst.x >= GAME_WIDTH || dst.x < -TILE_SIZE || dst.y >= GAME_HEIGHT || dst.y < -TILE_SIZE) return; // Only render the visible ones...
    SDL_RenderCopy(renderer, texture, &src, &dst);
    
    if(data.tileZ)
    {
        COLOR(renderer, 0x22FFFFFF); // brightness modifier = 0 -> nothing changed, = 0xFF -> full white
        SDL_RenderFillRect(renderer, &dst); // Render over the tile
    }
}
