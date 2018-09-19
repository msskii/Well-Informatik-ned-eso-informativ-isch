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

Tile::Tile(int x, int y, TileData d) : xcoord(x), ycoord(y), data(d)
{
    
}

Tile::Tile(int x, int y, uint16_t tileNumber, uint8_t zheight) : xcoord(x), ycoord(y), data({ tileNumber, zheight})
{

}

void Tile::reloadTexture()
{
    SDL_FreeSurface(Tile_surface);
    Tile_surface = loadTileVariant(data.tileNumber, data.variant);
}
