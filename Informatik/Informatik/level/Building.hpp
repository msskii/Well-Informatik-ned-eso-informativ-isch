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

#pragma pack(push, 1)
enum Buildings
{
    BUILDING_OLDMANHUT = 0,
    BUILDING_TAVERN,
    BUILDING_BLACKSMITH,
    DBUILDING_LADDERUP,
    DBUILDING_LADDERDOWN,
    DBUILDING_CAVEWALL
    
};

typedef struct BuildingData
{
    uint16_t buildingNumber;
    uint16_t buildingVariant;
    uint8_t sizeX;
    uint8_t sizeY;
    int xcoord;
    int ycoord;
    float hitboxX;
    float hitboxY;
    float hitboxsizeX;
    float hitboxsizeY;
    float hitboxXBehind;
    float hitboxYBehind;
    float hitboxsizeXBehind;
    float hitboxsizeYBehind;
} BuildingData;
#pragma pack(pop)

class Level;

class Building
{
private:
    SDL_Surface *building_surface = nullptr;
    gl_texture texture;
    char brightness_modifier = 0;
    Level *level;
    bool enableColision = true;
    
public:
    BuildingData data;
    Building(int x, int y, uint16_t buildingnumber, uint16_t buildingVariant, Level *level);
    Building(BuildingData d, Level *level);
    void render(int xoff, int yoff);
    bool isInside(float x, float y);
    bool isInside(float x, float y, bool overrule);
    bool isBehind(float x, float y);
};


#endif /* Building_hpp */
