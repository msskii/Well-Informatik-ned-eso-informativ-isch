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
        case GRASS:
            switch (variant)
            {
                    // 0 - 127: Design
                    // 128 - 254: Transitions between Tiles
                case 0:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass.png"));
<<<<<<< HEAD
                case 1:
=======
                case STONE_ROAD_ON_GRASS:
>>>>>>> 32b8dbf4259057381a81fbd7effcd42113453d63
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

void updateVariant(Level *level)
{
<<<<<<< HEAD
    return loadTileVariant(tileNumber, variant); // Variant is
}

void updateVariant(Tile *tiles, int w, int h)
{
    for(int i = 0; i < w * h; i++)
    {
        //check if Grass is surrounded by Dirt
        tiles[i].data.variant = rand() % 100;
        if(tiles[i].data.tileNumber == GRASS)
=======
    for(int i = 0; i < level->width * level->height; i++)
    {
        //check if Grass is surrounded by Dirt
        if(level->tiles[i].data.tileNumber == GRASS)
>>>>>>> 32b8dbf4259057381a81fbd7effcd42113453d63
        {
            // syntax: 0 0 0 0 left up right down
            uint8_t type = 0;
            
            // Bitwise operators! Keanu pls
            
            //left always checks if in bounds
<<<<<<< HEAD
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
=======
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
>>>>>>> 32b8dbf4259057381a81fbd7effcd42113453d63
        }
    }
}
