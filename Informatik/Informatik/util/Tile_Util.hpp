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

#define NUMBER_OF_TEXTURES 3

enum Textures
{
    GRASS = 0,
    STONE_ROAD_ON_GRASS,
    DIRT
};

typedef struct TextureInformation
{
    const char *textureName;
    int numberOfVariants;
} TextureInformation;

const TextureInformation textureData[NUMBER_OF_TEXTURES] =
{
    {"Grass",       17}, // 17 variants of grass --> 1 normal & 16 other ones
    {"Stone path",  1},
    {"Dirt",        1}
};

extern SDL_Surface *loadTileVariant(uint16_t tileNumber, uint8_t variant);
extern void updateVariant(Level *l, SDL_Renderer *renderer);

#endif /* Tile_Util_hpp */
