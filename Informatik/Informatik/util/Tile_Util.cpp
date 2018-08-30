//
//  Tile_Util.cpp
//  Informatik
//
//  Created by Aaron Hodel on 29.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Tile_Util.hpp"
#include <stdlib.h>

SDL_Surface *loadTileVariant(uint16_t tileNumber, uint8_t variant)
{
    switch (tileNumber)
    {
        case 0:
            switch (variant)
            {
                case 0:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass_1.png"));
                case 1:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass_2.png"));
                default:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass.png"));
            }
        case 1:
            return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_StonerPathOnGrass.png"));
        case 2:
            return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_StonerPathOnGrass.png"));
            
        default:
            return NULL;
    }
}

SDL_Surface *loadTile(uint16_t tileNumber, uint8_t &variant)
{
    variant = rand() % 100;
    return loadTileVariant(tileNumber, variant); // Variant is
}
