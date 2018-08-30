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
    uint8_t variant;
} TileData;
#pragma pack(pop)

class Tile
{
private:
    SDL_Surface *Tile_surface = nullptr;
    SDL_Texture *texture = nullptr;
    int xcoord, ycoord;
    char brightness_modifier = 0;
    
public:
    Tile();
    TileData data = {0, 0};
    Tile(int x, int y, uint16_t tilenumber);
    Tile(int x, int y, uint16_t tilenumber, uint8_t zheight);

    void reloadTexture();
    void reloadTexture(int variant);
    void render(SDL_Renderer *renderer, int xoff, int yoff);
};

#endif /* Tile_hpp */
