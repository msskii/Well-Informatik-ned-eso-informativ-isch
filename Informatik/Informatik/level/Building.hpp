//
//  Building.hpp
//  Informatik
//
//  Created by Keanu Gleixner on 11.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Building_hpp
#define Building_hpp

#include "../util/Tile_Util.hpp"
#include "../util/SDL_Util.hpp"
#include "../config.h"

#include <stdio.h>

typedef struct BuildingData
{
    uint16_t buildingNumber;
    uint8_t sizeX;
    uint8_t sizeY;
    
} BuildingData;


class Building
{
private:
    SDL_Surface *building_surface = nullptr;
    SDL_Texture *texture = nullptr;
    int xcoord, ycoord;
    char brightness_modifier = 0;
    
public:
    BuildingData data;
    Building(int x, int y, uint16_t buildingnumber);
    Building();
    void render(SDL_Renderer *renderer, int xoff, int yoff);
    bool isInside(float x, float y);
};


#endif /* Building_hpp */
