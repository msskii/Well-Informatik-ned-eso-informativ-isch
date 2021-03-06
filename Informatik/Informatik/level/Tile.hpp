//
//  Tile.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include "../util/SDL_Util.hpp"
#include "../util/Tile_Util.hpp"
#include "../config.h"

#pragma pack(push, 1)
typedef struct TileData
{
    uint16_t tileNumber;
    uint8_t tileZ;
    uint8_t variant = 0;
} TileData;
#pragma pack(pop)

class Tile
{
private:
    
    char brightness_modifier = 0;
    
public:
    int xcoord, ycoord;
    SDL_Surface *Tile_surface = nullptr;

    Tile();
    TileData data = {0, 0};
    Tile(int x, int y, uint16_t tilenumber);
    Tile(int x, int y, uint16_t tilenumber, uint8_t zheight);
    Tile(int x, int y, TileData data);

    void reloadTexture();
};

#endif /* Tile_hpp */
