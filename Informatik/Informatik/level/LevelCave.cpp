//
//  LevelCave.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 30.10.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "LevelCave.hpp"
#include "Level.hpp"

LevelCave::LevelCave()
{
    
}

void LevelCave::startCave(Level *&level)
{
    nextLevel(level);
}

void LevelCave::nextLevel(Level *&level)
{
    floor++;
    
    //create a new layer with the cave Gen
    level = new Level(width, height);
    LevelGen levelGen(width, height);
    int mapLayout[width * height];
    levelGen.returnMap(mapLayout);
    
    
    //translate the int array from the cave gen to level
    //also search the entrance
    for (int i = 0; i < height * width; i++)
    {
        switch (mapLayout[i]) {
            case WALL:
                level->tiles[i].data.tileNumber = 2;
                level->tiles[i].data.tileZ = 1;
                break;
                
            case DIRT:
                level->tiles[i].data.tileNumber = 0;
                break;
                
            case ENTRANCE:
                level->tiles[i].data.tileNumber = 1;
                level->getLocalPlayer()->moveTo((i % width) * TILE_SIZE, int(i/width) * TILE_SIZE);
                break;
                
            default:
                break;
        }
        level->tiles[i].reloadTexture();
    }
}
