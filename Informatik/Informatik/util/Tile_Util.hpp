//
//  Tile_Util.hpp
//  Informatik
//
//  Created by Aaron Hodel on 29.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Tile_Util_hpp
#define Tile_Util_hpp

#include "SDL_Util.hpp"
class Tile;
class Level;

#define NUMBER_OF_TEXTURES 4

enum Textures
{
    TILE_EMPTY = 0,
    TILE_GRASS,
    TILE_STONE_ROAD_ON_GRASS,
    TILE_DIRT
};


typedef struct TextureInformation
{
    const char *textureName;
    int numberOfVariants;
} TextureInformation;

const TextureInformation textureData[NUMBER_OF_TEXTURES] =
{
    {"Empty", 0},
    {"Grass",       17}, // 17 variants of grass --> 1 normal & 16 other ones
    {"Stone path",  1},
    {"Dirt",        1}
};

extern SDL_Surface *loadTileVariant(uint16_t tileNumber, uint8_t variant);
extern void updateVariant(Level *l);

#endif /* Tile_Util_hpp */
