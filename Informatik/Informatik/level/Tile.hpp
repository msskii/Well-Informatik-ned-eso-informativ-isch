//
//  Tile.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#define TILE_SIZE 50

#include "../util/SDL_Util.hpp"

#pragma pack(push, 1)
typedef struct SerializedTile
{
    uint16_t tileNumber;
    uint8_t tileZ;
} SerializedTile;
#pragma pack(pop)

class Tile
{
private:
    int xcoord, ycoord;
    
public:
    Tile();
    Tile(int x, int y);

    SerializedTile data = {0x00FF, 0}; // defaults
    
    void render(SDL_Renderer *renderer, int xoff, int yoff);
};

#endif /* Tile_hpp */
