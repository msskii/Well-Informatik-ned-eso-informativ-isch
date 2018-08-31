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
<<<<<<< HEAD
                case 0:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass.png"));
                case 1:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass_1.png"));
                case 2:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass_2.png"));
                case 129:
                    return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_GrassToDirt_0001.png"));
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
        case STONE_ROAD_ON_GRASS:
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
=======
                case GRASS:
                    return IMG_Load(GET_TEXTURE_PATH("/Tile_Grass"));
                case STONE_ROAD_ON_GRASS:
                    return IMG_Load(GET_TEXTURE_PATH("/Tile_Grass_1"));
                case 2:
                    return IMG_Load(GET_TEXTURE_PATH("/Tile_Grass_2"));
                case 128: 
                    return IMG_Load(GET_TEXTURE_PATH("/Tile_Grass_2"));
                default:
                    return IMG_Load(GET_TEXTURE_PATH("/Tile_Grass"));
            }
        case 1:
            return IMG_Load(GET_TEXTURE_PATH("/Tile_StonerPathOnGrass"));
        case 2:
            return IMG_Load(GET_TEXTURE_PATH("/Tile_StonerPathOnGrass"));
>>>>>>> 1d52ce2a5bcb1dade5c1a778e797cfd8ac3505ec
            
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
            
            //Ich han Bitwise operatore gha aber es het ned gfunkt demit also han ichs me em andere gmacht XD
            
            //left always checks if in bounds

            if(i % level->width != 0 && level->tiles[i - 1].data.tileNumber == DIRT) type |= 8;
            //up
            if(i >= level->width && level->tiles[i - level->width].data.tileNumber == DIRT) type |= 4;
            //right
            if((i + 1) % level->width != 0 && level->tiles[i + 1].data.tileNumber == DIRT) type |= 2;
            //down
            if(i / level->width + 1 < level->height && level->tiles[i + level->width].data.tileNumber == DIRT) type |= 1;
            
<<<<<<< HEAD
            level->tiles[i].data.variant = 128 + type;
=======
            // Maybe also do it like this? Just a proposition...
            GET_VARIANT_PATH("grass", type);
            
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
>>>>>>> 1d52ce2a5bcb1dade5c1a778e797cfd8ac3505ec
            
            level->tiles[i].reloadTexture(); // Reload the texture now...
        }
    }
}
