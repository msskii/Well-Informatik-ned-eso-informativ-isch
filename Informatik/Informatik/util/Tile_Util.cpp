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
            if(variant >= 129 && variant <= 128 + 0xF) return IMG_Load(GET_VARIANT_PATH("/Tile_GrassToDirt_", variant - 128)); // Different variants
            
            switch (variant)
            {
                    // 0 - 127: Design
                    // 128 - 254: Transitions between Tiles
                case 0:
                    return IMG_Load(GET_TEXTURE_PATH("/Tile_Grass"));
                case 1:
                    return IMG_Load(GET_TEXTURE_PATH("/Tile_Grass_1"));
                case 2:
                    return IMG_Load(GET_TEXTURE_PATH("/Tile_Grass_2"));
                default:
                    return IMG_Load(GET_TEXTURE_PATH("/Tile_Grass"));;
            }
        case STONE_ROAD_ON_GRASS:
            return IMG_Load(GET_TEXTURE_PATH("/Tile_StonerPathOnGrass"));
        case DIRT:
            switch (variant) 
			{
                case 0:
                    return IMG_Load(GET_TEXTURE_PATH("/Tile_Dirt"));
                case 1:
                    return IMG_Load(GET_TEXTURE_PATH("/Tile_Dirt_1"));
                case 2:
                    return IMG_Load(GET_TEXTURE_PATH("/Tile_Dirt_2"));
                case 3:
                    return IMG_Load(GET_TEXTURE_PATH("/Tile_Dirt_3"));
                default:
                    return IMG_Load(GET_TEXTURE_PATH("/Tile_Dirt"));
            }

            
        default:
            return NULL;
    }
}

void updateVariant(Level *level)
{
    for(uint64_t i = 0; i < level->width * level->height; i++)
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
            
            level->tiles[i].data.variant = 128 + type;
            // Maybe also do it like this? Just a proposition...
            
            level->tiles[i].reloadTexture(); // Reload the texture now...
        }
    }
}
