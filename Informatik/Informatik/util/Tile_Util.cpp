//
//  Tile_Util.cpp
//  Informatik
//
//  Created by Aaron Hodel on 29.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Tile_Util.hpp"

SDL_Surface *loadTile(uint16_t tileNumber)
{
    switch (tileNumber)
    {
        case 0:
            return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_Grass.png"));
            break;
        case 1:
            return IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/Tile_StonerPathOnGrass.png"));
            break;
    }
    
    return NULL;
}
