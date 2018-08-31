//
//  Tile_Util.cpp
//  Informatik
//
//  Created by Aaron Hodel on 29.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Tile_Util.hpp"
#include <stdlib.h>
#include "../level/Tile.hpp"
#include "../level/Level.hpp"

SDL_Surface *loadTileVariant(uint16_t tileNumber, uint8_t variant)
{
    switch (tileNumber)
    {
        case 0:
            switch (variant)
            {
                    // 0 - 127: Design
                    // 128 - 254: Transitions between Tiles
                case GRASS:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass.png"));
                case STONE_ROAD_ON_GRASS:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass_1.png"));
                case 2:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass_2.png"));
                case 128: 
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

void updateVariant(Level *level)
{
    for(int i = 0; i < level->width * level->height; i++)
    {
        //check if Grass is surrounded by Dirt
        if(level->tiles[i].data.tileNumber == GRASS)
        {
            // syntax: 0 0 0 0 left up right down
            uint8_t type = 0;
            
            // Bitwise operators! Keanu pls
            
            //left always checks if in bounds
            if(i % level->width != 0 && level->tiles[i - 1].data.tileNumber == DIRT) type |= 8;
            //up
            if(i >= level->width && level->tiles[i - level->width].data.tileNumber == DIRT) type |= 4;
            //right
            if((i + 1) % level->width != 0 && level->tiles[i + 1].data.tileNumber == DIRT) type |= 2;
            //down
            if(i / level->width + 1 < level->height && level->tiles[i + level->width].data.tileNumber == DIRT) type |= 1;
            
            
            switch (type)
            {
                case 0:
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    break;
                case 10:
                    break;
                case 11:
                    break;
                case 12:
                    break;
                case 13:
                    break;
                case 14:
                    break;
                case 15:
                    break;
                default:
                    break;
            }
            
            level->tiles[i].reloadTexture(); // Reload the texture now...
        }
    }
}
