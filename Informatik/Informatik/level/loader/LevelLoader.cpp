//
//  LevelLoader.cpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "LevelLoader.hpp"

int readInt(uint8_t *&levelFile)
{
    levelFile += 4;
    return ((uint32_t*)(levelFile - 4))[0];
}

Level *loadLevel(const char *path, int w, int h)
{
    uint8_t* file = nullptr; //readFile(path); // Enable loading the level file here
    if(file == nullptr)
    {
        return new Level(w, h);
    }
    else
    {
        return LevelLoader(path).buildLevel();
    }
}

LevelLoader::LevelLoader(Level *l) : level(l)
{
    
}

LevelLoader::LevelLoader(const char *path)
{
    INFO("Loading Level");

    uint8_t *levelFile = readFile(path);
    if(levelFile == nullptr) return;
    
    uint32_t width = readInt(levelFile);
    uint32_t height = readInt(levelFile);
    
    level = new Level(width, height);
    for(int i = 0; i < (int)(width * height); i++)
    {
        level->tiles[i].data = ((SerializedTile*) levelFile)[0];
        levelFile += sizeof(SerializedTile);
    }
    
    // Load background music
    uint32_t musicLength = readInt(levelFile);
    char *musicPath = (char*) malloc(musicLength + 1); // With null terminator
    memcpy(musicPath, levelFile, musicLength);
    musicPath[musicLength] = 0;
    level->audioFile = musicPath;
    levelFile += musicLength;
    
    // Load TileMapFile
    uint32_t tileMapLength = readInt(levelFile);
    char *tileMapPath = (char*) malloc(tileMapLength + 1); // With null terminator
    memcpy(tileMapPath, levelFile, tileMapLength);
    tileMapPath[tileMapLength] = 0;
    level->tileMapFile = tileMapPath;
    levelFile += tileMapLength;

    // Load events
    level->events = loadEventData(levelFile);
}

Level *LevelLoader::buildLevel()
{
    return level;
}

void LevelLoader::saveFile(const char *path)
{
    // 4: width
    // 4: height
    // width * height * sizeof(SerializedTile)
    int size = level->getLevelSize() + level->getEventSize(); // level tiles
    
    uint8_t *levelFile = (uint8_t *) malloc(size);
    
    INFO("Saving Level");
    
    ((uint32_t*) levelFile)[0] = level->width;
    ((uint32_t*) levelFile)[1] = level->height;
    
    levelFile += 8; // Move pointer 8 to the front --> start of tiles
    for(int i = 0; i < (int)(level->width * level->height); i++)
    {
        ((SerializedTile*) levelFile)[0] = level->tiles[i].data;
        levelFile += sizeof(SerializedTile);
    }
    
    // Paths

    int musicLength = (int) strlen(level->audioFile);

    ((uint32_t*) levelFile)[0] = musicLength;
    levelFile += 4;
    memcpy(levelFile, level->audioFile, musicLength);
    levelFile += musicLength;
    
    int tileMapLength = (int) strlen(level->tileMapFile);
    ((uint32_t*) levelFile)[0] = tileMapLength;
    levelFile += 4;
    memcpy(levelFile, level->tileMapFile, tileMapLength);
    levelFile += tileMapLength;

    // Events
    saveEventData(levelFile, level->events); // Save events
    levelFile += level->getEventSize(); // End of current data
    
    levelFile -= size; // Back to start
    writeFile(path, levelFile, size);
}
