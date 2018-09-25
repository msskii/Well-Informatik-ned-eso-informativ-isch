//
//  LevelLoader.cpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "LevelLoader.hpp"

template <typename T>
T Loader::read(uint8_t *&levelFile)
{
    T a = ((T*) levelFile)[0];
    levelFile += sizeof(T);
    return a;
}

template <typename T>
void Loader::write(uint8_t *&levelFile, T value)
{
    ((T*) levelFile)[0] = value;
    levelFile += sizeof(T);
}

char *Loader::readString(uint8_t *&levelFile)
{
    int length = read<int>(levelFile);
    char *str = (char*) malloc(length + 1); // With null terminator
    memcpy(str, levelFile, length);
    str[length] = 0;
    levelFile += length;
    return str;
}

void Loader::writeString(uint8_t *&levelFile, const char *text, int length)
{
    write<int>(levelFile, length);
    memcpy(levelFile, text, length);
    levelFile += length;
}

Level *Loader::loadLevel(const char *path, int w, int h)
{
     uint8_t *file = nullptr;
    //uint8_t* file = readFile(path).data; // Enable loading the level file here
    if(file == nullptr)
    {
        Level *l = new Level(w, h);
        l->levelFile = std::string(path);
        l->reloadFiles();
        return l;
    }
    else
    {
        Level *l = Loader::LevelLoader(path).buildLevel();
        if(l == nullptr) l = new Level(w, h);
        l->levelFile = std::string(path);
        l->reloadFiles();
        return l;
    }
}

Loader::LevelLoader::LevelLoader(Level *l) : level(l)
{
    
}

Loader::LevelLoader::LevelLoader(const char *path)
{
    printf("[INFO] Loading Level from file: %s\n", path);

    uint8_t *levelFile = readFile(path).data;
    if(levelFile == nullptr) return;
    
    uint32_t loader_version = read<int>(levelFile);
    
    // First major version is version 3 (1 & 2 not supported)
    if(loader_version == 3)
    {
        uint32_t width = read<int>(levelFile);
        uint32_t height = read<int>(levelFile);
        
        level = new Level(width, height);
        for(int i = 0; i < (int)(width * height); i++)
        {
            level->tiles[i] = Tile(i % level->width, i / level->width, read<TileData>(levelFile));
            level->tiles[i].reloadTexture();
        }
        
        uint32_t numbuildings = read<int>(levelFile);
        Building *buildings = (Building*) malloc(sizeof(Building) * numbuildings); // Don't call constructor... so no constructor is needed
        for(int i = 0; i < numbuildings; i++) buildings[i] = Building(read<BuildingData>(levelFile), level);
        
        level->audioFile = readString(levelFile);
        level->textFile = readString(levelFile);
        level->tileMapFile = readString(levelFile);
        level->reloadFiles();
        
        level->events = loadEventData(levelFile);
    }
    else
    {
        printf("[ERROR] Unsupported level version: %d. Current Version: %d\n", loader_version, LOADER_VERSION);
    }
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
    int size = level->getLevelSize() + level->getEventSize() + 4; // level tiles
    
    uint8_t *levelFile = (uint8_t *) malloc(size);
    write<int>(levelFile, (int) LOADER_VERSION);
    
    printf("[INFO] Saving Level to %s (Version of loader: %d)\n", path, (int) LOADER_VERSION);
    
    write<int>(levelFile, level->width);
    write<int>(levelFile, level->height);    
    for(int i = 0; i < (int)(level->width * level->height); i++) write<TileData>(levelFile, level->tiles[i].data);
    
    write<int>(levelFile, (int) level->buildings.size());
    for(int i = 0; i < level->buildings.size(); i++) write<BuildingData>(levelFile, level->buildings[i]->data);
    
    // Paths
    writeString(levelFile, level->audioFile.c_str(), (int) level->audioFile.size());
    writeString(levelFile, level->textFile.c_str(), (int) level->textFile.size());
    writeString(levelFile, level->tileMapFile.c_str(), (int) level->tileMapFile.size());

    // Events
    saveEventData(levelFile, level->events); // Save events
    levelFile += level->getEventSize(); // End of current data
    
    levelFile -= size; // Back to start
    writeFile(path, levelFile, size);
}
