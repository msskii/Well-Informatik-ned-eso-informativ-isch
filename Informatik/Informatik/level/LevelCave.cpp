//
//  LevelCave.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 30.10.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "LevelCave.hpp"
#include "Event.hpp"

LevelCave::LevelCave(Level *&plevel) : level(plevel)
{
}

void LevelCave::startCave()
{
    floor = 0;
    nextLevel();
}

void LevelCave::nextLevel()
{
    floor++;
    
    Window *w = level->window;
    //create a new layer with the cave Gen
    level = new Level(width, height);
    LevelGen levelGen(width, height);
    int mapLayout[width * height];
    levelGen.returnMap(mapLayout);
    level->window = w;

    
    //translate the int array from the cave gen to level
    //also search the entrance
    EventData eventData;
    for (int i = 0; i < height * width; i++)
    {
        switch (mapLayout[i])
        {
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
            case EXIT:
                eventData.event_x = TILE_SIZE * (i % width);
                eventData.event_y = TILE_SIZE * int(i/width);
                eventData.event_w = TILE_SIZE;
                eventData.event_h = TILE_SIZE;
                eventData.event_action = CAVE_NEXT_LEVEL;
                eventData.event_type_filter = STEP_ON;
                eventData.triggerAmount = 0; // As many times triggered as you want
                eventData.event_id_dependency = 0; // No Event needs to be triggered first
                eventData.event_id = 0; // Auto increment & start from one
                
                level->events.push_back(new Event(eventData, new uint8_t[1] {0})); // 
                
                
            default:
                break;
        }
        level->tiles[i].reloadTexture();
    }
    //reload level
    level->update();
    level->updateTiles();
    level->reloadFiles();
}
