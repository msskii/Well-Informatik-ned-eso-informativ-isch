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
        case TILE_GRASS:
            if(variant >= 129 && variant <= 128 + 0xF) return IMG_Load(GET_VARIANT_PATH("tiles/Tile_GrassToDirt_", variant - 128)); // Different variants
            
            switch (variant)
            {
                    // GET_TEXTURE_PATH gives the path from the texture, it appends .png, so it can be left out here
                    // GET_VARIANT_PATH gives the path from a certain variant, it does so by appending the variant number to the end of the path
                    
                    // 0 - 100: Design
                    // 101 - 127: Buildings
                    // 128 - 254: Transitions between Tiles
                case 0:
                    return IMG_Load(GET_TEXTURE_PATH("tiles/Tile_Grass"));
                case 1:
                    return IMG_Load(GET_TEXTURE_PATH("tiles/Tile_Grass_1"));
                case 2:
                    return IMG_Load(GET_TEXTURE_PATH("tiles/Tile_Grass_2"));
                default:
                    return IMG_Load(GET_TEXTURE_PATH("tiles/Tile_Grass"));;
            }
            
        case TILE_STONE_ROAD_ON_GRASS:
            return IMG_Load(GET_TEXTURE_PATH("tiles/Tile_StonerPathOnGrass"));
            
        case TILE_DIRT:
            if(variant >= 129 && variant <= 128 + 0x1F) return IMG_Load(GET_VARIANT_PATH("tiles/Tile_Dirtboarder_", variant - 128));
            switch (variant) 
			{
                case 0:
                    return IMG_Load(GET_TEXTURE_PATH("tiles/Tile_Dirt"));
                case 1:
                    return IMG_Load(GET_TEXTURE_PATH("tiles/Tile_Dirt_1"));
                case 2:
                    return IMG_Load(GET_TEXTURE_PATH("tiles/Tile_Dirt_2"));
                case 3:
                    return IMG_Load(GET_TEXTURE_PATH("tiles/Tile_Dirt_3"));
                default:
                    return IMG_Load(GET_TEXTURE_PATH("tiles/Tile_Dirt"));
            }
            
        case TILE_EMPTY:
            return NULL;
            
        default:
            return NULL;
    }
}

void updateVariant(Level *level)
{
    for(uint64_t i = 0; i < level->width * level->height; i++)
    {
        //check if Grass is surrounded by Dirt
        if(level->tiles[i].data.tileNumber == TILE_GRASS)
        {
            // syntax: 0 0 0 0 left up right down
            uint8_t type = 0;
            //left always checks if in bounds

            if(i % level->width != 0 && level->tiles[i - 1].data.tileNumber == TILE_DIRT) type |= 8;
            //up
            if(i >= level->width && level->tiles[i - level->width].data.tileNumber == TILE_DIRT) type |= 4;
            //right
            if((i + 1) % level->width != 0 && level->tiles[i + 1].data.tileNumber == TILE_DIRT) type |= 2;
            //down
            if(i / level->width + 1 < level->height && level->tiles[i + level->width].data.tileNumber == TILE_DIRT) type |= 1;
            
            level->tiles[i].data.variant = 128 + type;
            // Maybe also do it like this? Just a proposition...
            level->tiles[i].reloadTexture();
        }
        else if(level->tiles[i].data.tileNumber == TILE_DIRT)
        {
            uint8_t type = 0;
            if(i % level->width != 0 && level->tiles[i - 1].data.tileNumber == TILE_EMPTY) type |= 8;
            //up
            if(i >= level->width && level->tiles[i - level->width].data.tileNumber == TILE_EMPTY) type |= 4;
            //right
            if((i + 1) % level->width != 0 && level->tiles[i + 1].data.tileNumber == TILE_EMPTY) type |= 2;
            //down
            if(i / level->width + 1 < level->height && level->tiles[i + level->width].data.tileNumber == TILE_EMPTY) type |= 1;
            if (!(type == 8 || type == 4 || type == 2 || type == 1) && type != 0) {
                //add random mutations
                
                if (rand() % 20 == 0)
                {
                    level->tiles[i].data.variant = 128 + type + 16;
                }
                else
                {
                    level->tiles[i].data.variant = 128 + type;

                }
                level->tiles[i].reloadTexture();
            }
            
        }
    }
    level->updateTiles();
}
