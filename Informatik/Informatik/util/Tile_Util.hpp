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
    STONEROADONGRASS,
    DIRT
};

typedef struct TextureInformation
{
    const char *textureName;
} TextureInformation;

const TextureInformation textureData[NUMBER_OF_TEXTURES] = {
    {"Grass"},
    {"Stone path"},
    {"Dirt"}
};

extern SDL_Surface *loadTileVariant(uint16_t tileNumber, uint8_t variant);
extern SDL_Surface *loadTile(uint16_t tileNumber, uint8_t &variant);
extern void updateVariant(Level *l);

#endif /* Tile_Util_hpp */
