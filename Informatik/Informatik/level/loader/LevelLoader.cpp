//
//  LevelLoader.cpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "LevelLoader.hpp"

Level *loadLevel(const char *path, int w, int h)
{
    uint8_t* file = readFile(path);
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
    uint8_t *levelFile = readFile(path);
    uint32_t width = ((uint32_t*)levelFile)[0];
    uint32_t height = ((uint32_t*)levelFile)[1];
    
    level = new Level(width, height);
    levelFile += 8; // two uint32_t
    for(int i = 0; i < width * height; i++)
    {
        level->operator[](i).tileNumber = ((SerializedTile*) levelFile)[i].tileNumber;
        level->operator[](i).tileZ = ((SerializedTile*) levelFile)[i].tileZ;
    }
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
    int size = 4 + 4 + sizeof(SerializedTile) * level->width * level->height;
    uint8_t *levelFile = (uint8_t *) malloc(size);
    
    ((uint32_t*) levelFile)[0] = level->width;
    ((uint32_t*) levelFile)[1] = level->height;
    
    levelFile += 8; // Move pointer 8 to the front --> start of tiles
    for(int i = 0; i < level->width * level->height; i++)
    {
        SerializedTile tile = { level->operator[](i).tileNumber, level->operator[](i).tileZ };
        ((SerializedTile*) levelFile)[i] = tile;
    }
    levelFile -= 8;

    writeFile(path, levelFile, size);
}
