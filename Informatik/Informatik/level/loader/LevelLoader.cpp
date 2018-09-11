//
//  LevelLoader.cpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "LevelLoader.hpp"

int Loader::readInt(uint8_t *&levelFile)
{
    levelFile += 4;
    return ((uint32_t*)(levelFile - 4))[0];
}

Level *Loader::loadLevel(const char *path, int w, int h, SDL_Renderer *renderer)
{
    //uint8_t *file = nullptr;
    uint8_t* file = readFile(path).data; // Enable loading the level file here
    if(file == nullptr)
    {
        Level *l = new Level(w, h, renderer);
        l->reloadFiles();
        return l;
    }
    else
    {
        return Loader::LevelLoader(path, renderer).buildLevel();
    }
}

Loader::LevelLoader::LevelLoader(Level *l) : level(l)
{
    
}

Loader::LevelLoader::LevelLoader(const char *path, SDL_Renderer *renderer)
{
    printf("[INFO] Loading Level from file: %s\n", path);

    uint8_t *levelFile = readFile(path).data;
    if(levelFile == nullptr) return;
    
    uint32_t width = readInt(levelFile);
    uint32_t height = readInt(levelFile);
    
    level = new Level(width, height);
    for(int i = 0; i < (int)(width * height); i++)
    {
        level->tiles[i] = Tile(i % level->width, i / level->width, ((TileData*) levelFile)[0]);
        level->tiles[i].reloadTexture(renderer);
        levelFile += sizeof(TileData);
    }
    
    // Load background music
    uint32_t musicLength = readInt(levelFile);
    char *musicPath = (char*) malloc(musicLength + 1); // With null terminator
    memcpy(musicPath, levelFile, musicLength);
    musicPath[musicLength] = 0;
    level->audioFile = musicPath;
    levelFile += musicLength;
    
    // Load text file
    uint32_t textLength = readInt(levelFile);
    char *textPath = (char*) malloc(textLength + 1); // With null terminator
    memcpy(textPath, levelFile, textLength);
    textPath[textLength] = 0;
    level->textFile = textPath;
    levelFile += textLength;
    
    // Load TileMapFile
    uint32_t tileMapLength = readInt(levelFile);
    char *tileMapPath = (char*) malloc(tileMapLength + 1); // With null terminator
    memcpy(tileMapPath, levelFile, tileMapLength);
    tileMapPath[tileMapLength] = 0;
    level->tileMapFile = tileMapPath;
    levelFile += tileMapLength;
    
    level->reloadFiles();

    // Load events
    level->events = loadEventData(levelFile);
}

Level *Loader::LevelLoader::buildLevel()
{
    return level;
}

void Loader::LevelLoader::saveFile(const char *path)
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
        ((TileData*) levelFile)[0] = level->tiles[i].data;
        levelFile += sizeof(TileData);
    }
    
    // Paths
    printf("Audio path: %s\n", level->audioFile.c_str());
    int musicLength = (int) level->audioFile.size();
    ((uint32_t*) levelFile)[0] = musicLength;
    levelFile += 4;
    memcpy(levelFile, level->audioFile.c_str(), musicLength);
    levelFile += musicLength;
    
    int textLength = (int) level->textFile.size();
    ((uint32_t*) levelFile)[0] = textLength;
    levelFile += 4;
    memcpy(levelFile, level->textFile.c_str(), textLength);
    levelFile += textLength;
    
    int tileMapLength = (int) level->tileMapFile.size();
    ((uint32_t*) levelFile)[0] = tileMapLength;
    levelFile += 4;
    memcpy(levelFile, level->tileMapFile.c_str(), tileMapLength);
    levelFile += tileMapLength;

    // Events
    saveEventData(levelFile, level->events); // Save events
    levelFile += level->getEventSize(); // End of current data
    
    levelFile -= size; // Back to start
    writeFile(path, levelFile, size);
}
