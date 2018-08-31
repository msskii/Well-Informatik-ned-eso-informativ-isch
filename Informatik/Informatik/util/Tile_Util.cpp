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
#include "tile_ID.h"

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
                case STONEROADONGRASS:
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

SDL_Surface *loadTile(uint16_t tileNumber, uint8_t &variant)
{
    //variant = rand() % 100;
    return loadTileVariant(tileNumber, variant); // Variant is
}

void updateVariant(Tile *tiles, int w, int h)
{
    for(int i = 0; i < w * h; i++)
    {
        //check if Grass is surrounded by Dirt
        if(tiles[i].data.tileNumber == GRASS)
        {
            // syntax: 0 0 0 0 left up right down
            uint8_t type = 0;
            
            //left always checks if in bounds
            if(i % w != 0 && tiles[i-1].data.tileNumber == DIRT){
                type &= 8;
            }
            //up
            if(i - w >= 0 && tiles[i-w].data.tileNumber == DIRT){
                type &= 4;
            }
            //right
            if((i + 1) % w != 0 &&tiles[i+1].data.tileNumber == DIRT){
                type &= 2;
            }
            //down
            if(i + w < w * h && tiles[i+w].data.tileNumber == DIRT){
                type &= 1;
            }
            
            
            switch (type) {
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

            
        }
        
        
        
    }
}
