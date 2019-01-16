//
//  LevelCave.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 30.10.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "LevelCave.hpp"
#include "Event.hpp"
#include <time.h>

LevelCave::LevelCave(Level *&plevel, Window *w) : level(plevel), window(w)
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
    //create a new layer with the cave Gen
    level = new Level(width, height);
    LevelGen levelGen(width, height);
    levelGen.addGrasspatch(70, 1);
    int *mapLayout = new int[width * height];
    levelGen.returnMap(mapLayout);
    
    
    level->window = window;

    
    //translate the int array from the cave gen to level
    //also search the entrance
    EventData eventData;
    for (int i = 0; i < height * width; i++)
    {
        switch (mapLayout[i])
        {
            case WALL:
                level->tiles[i].data.tileNumber = TILE_EMPTY;
                level->tiles[i].data.tileZ = 1;
                if(i < ((height - 1) * width) && mapLayout[i+width] != WALL)
                {
                    level->buildings.push_back(new Building(i % width, int(i / width) - 1, DBUILDING_CAVEWALL, 0, level));
                    if(i > 2 * width && mapLayout[i - 2 * width] != WALL)
                    {
                        level->tiles[i - 2 * width].data.tileNumber = TILE_EMPTY;
                        level->tiles[i - 2 * width].data.tileZ = 1;
                    }
                }
                break;
                
            case GRASS:
                level->tiles[i].data.tileNumber = TILE_GRASS;
                break;
                
            case DIRT:
                level->tiles[i].data.tileNumber = TILE_DIRT;
                break;
                
            case ENTRANCE:
                entranceSet = true;
                level->buildings.push_back(new Building(i % width, int(i / width) - 2, DBUILDING_LADDERUP, 0, level));
                level->tiles[i].data.tileNumber = TILE_DIRT;
                level->getLocalPlayer()->moveTo((float) (i % width) * TILE_SIZE, (float) int(i / width) * TILE_SIZE);
                break;
            case EXIT:
                exitSet = true;
                level->buildings.push_back(new Building(i % width, int(i / width), DBUILDING_LADDERDOWN, 0, level));
                level->tiles[i].data.tileNumber = TILE_DIRT;
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
                break;
                
            default:
                break;
        }
        //add random muation tile
    }
    for(int i = 0; i < width * height; i++)
    {
        level->tiles[i].data.variant = rand() % 200 <= 2 ? 1 : rand() % 200 <= 2 ? 2 : 0; // Add stuff to the level
        level->tiles[i].reloadTexture();
    }
    
    if (exitSet)
    {
        updateVariant(level);
        //add enemies
        if(floor < 10)
        {
            //add n slimes
            for (int i = 0; i < 10; i++) {
                //try n times
                for (int j = 0; j < 50; j++) {
                    int x = rand() % (width * height);
                    if (mapLayout[x] != WALL && mapLayout[x] != EXIT && mapLayout[x] != ENTRANCE) {
                        Slime *slime = new Slime((float) (x % width) * TILE_SIZE, (float) int(x/width) * TILE_SIZE, floor * 2);
                        level->addEntity(slime);
                        break;
                    }
                }
            }
        }
        else if(floor == 10)
        {
            
        }
        //reload level
        level->update();
        level->updateTiles();
        level->reloadFiles();
        entranceSet = false;
        exitSet = false;
      
    }else
    {
        entranceSet = false;
        floor--;
        nextLevel();
    }
    
    
}
