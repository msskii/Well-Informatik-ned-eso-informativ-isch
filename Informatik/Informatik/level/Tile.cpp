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
    Tile_surface = loadTile(data.tileNumber, data.variant);
}

Tile::Tile(int x, int y, uint16_t tileNumber) : xcoord(x), ycoord(y), data({ tileNumber, 0})
{
    Tile_surface = loadTile(tileNumber, data.variant);
}

Tile::Tile(int x, int y, uint16_t tileNumber, uint8_t zheight) : xcoord(x), ycoord(y), data({ tileNumber, zheight})
{

    Tile_surface = loadTile(tileNumber, data.variant);
}

void Tile::reloadTexture()
{
    texture = nullptr;
    Tile_surface = loadTile(data.tileNumber, data.variant);
}

void Tile::reloadTexture(int variant) // For the tileeditor
{
    texture = nullptr;
    Tile_surface = loadTileVariant(data.tileNumber, variant);
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
    
    if(dst.x >= GAME_WIDTH || dst.x < -TILE_SIZE || dst.y >= GAME_HEIGHT || dst.y < -TILE_SIZE) return; // Only render the visible ones...
    SDL_RenderCopy(renderer, texture, &src, &dst);
    
    /**
    if(brightness_modifier > 0)
    {
        COLOR(renderer, (brightness_modifier << 24) | 0xFFFFFF); // brightness modifier = 0 -> nothing changed, = 0xFF -> full white
    }
    else
    {
        COLOR(renderer, (-brightness_modifier << 24) | 0x000000); // brightness modifier = 0 -> nothing changed, = 0xFF -> full black
    }
    SDL_RenderFillRect(renderer, &dst); // Render over the tile
    */
    if(data.tileZ)
    {
        COLOR(renderer, 0x22FFFFFF); // brightness modifier = 0 -> nothing changed, = 0xFF -> full white
        SDL_RenderFillRect(renderer, &dst); // Render over the tile
    }
}
