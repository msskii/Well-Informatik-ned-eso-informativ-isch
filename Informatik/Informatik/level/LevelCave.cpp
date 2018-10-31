//
//  LevelCave.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 30.10.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "LevelCave.hpp"

LevelCave::LevelCave(Level *level)
{
    nextLevel(level);
}

void LevelCave::nextLevel(Level *oldLevel)
{
    floor++;
    
    //create a new layer with the cave Gen
    Level *level = new Level(width, height);
    LevelGen levelGen(width, height);
    int mapLayout[width * height];
    levelGen.returnMap(mapLayout);
    
    //translate the int array from the cave gen to level
    for (int i = 0; i < height * width; i++)
    {
        level->tiles[i].data.tileNumber = mapLayout[i];
    }
    oldLevel = level;
}
