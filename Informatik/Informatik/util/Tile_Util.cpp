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
        case GRASS:
            switch (variant)
            {
                    // 0 - 127: Design
                    // 128 - 254: Transitions between Tiles
                case 0:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass.png"));
                case 1:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass_1.png"));
                case 2:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass_2.png"));
                case 130:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_GrassToDirt_0010.png"));
                case 131:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_GrassToDirt_0011.png"));
                case 132:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_GrassToDirt_0100.png"));
                case 133:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_GrassToDirt_0101.png"));
                case 134:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_GrassToDirt_0110.png"));
                case 135:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_GrassToDirt_0111.png"));
                case 136:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_GrassToDirt_1000.png"));
                case 137:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_GrassToDirt_1001.png"));
                case 138:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_GrassToDirt_1010.png"));
                case 139:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_GrassToDirt_1011.png"));
                case 140:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_GrassToDirt_1100.png"));
                case 141:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_GrassToDirt_1101.png"));
                case 142:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_GrassToDirt_1110.png"));
                case 143:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_GrassToDirt_1111.png"));
                default:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass.png"));;
            }
        case STONEROADONGRASS:
            return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_StonerPathOnGrass.png"));
        case DIRT:
            switch (variant) {
                case 0:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Dirt.png"));
                case 1:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Dirt_1.png"));
                case 2:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Dirt_2.png"));
                case 3:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Dirt_3.png"));
                default:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Dirt.png"));;
            }
            
        default:
            return NULL;
    }
}

SDL_Surface *loadTile(uint16_t tileNumber, uint8_t &variant)
{
    return loadTileVariant(tileNumber, variant); // Variant is
}

void updateVariant(Tile *tiles, int w, int h)
{
    for(int i = 0; i < w * h; i++)
    {
        //check if Grass is surrounded by Dirt
        tiles[i].data.variant = rand() % 100;
        if(tiles[i].data.tileNumber == GRASS)
        {
            // syntax: 0 0 0 0 left up right down
            uint8_t type = 0;
            
            //left always checks if in bounds
            if(i % w != 0 && tiles[i-1].data.tileNumber == DIRT){
                type += 8;
            }
            //up
            if(i - w >= 0 && tiles[i-w].data.tileNumber == DIRT){
                type += 4;
            }
            //right
            if((i + 1) % w != 0 &&tiles[i+1].data.tileNumber == DIRT){
                type += 2;
            }
            //down
            if(i + w < w * h && tiles[i+w].data.tileNumber == DIRT){
                type += 1;
            }
            tiles[i].data.variant = 128 + type;
        }
        
        
        
    }
}
