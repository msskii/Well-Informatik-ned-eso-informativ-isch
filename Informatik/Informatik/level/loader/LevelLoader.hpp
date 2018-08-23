//
//  LevelLoader.hpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef LevelLoader_hpp
#define LevelLoader_hpp

#include "../../util/FileReader.hpp"
#include "../Level.hpp"
#include "EventLoader.hpp"

static int readInt(uint8_t *&levelFile)
{
    levelFile += 4;
    return ((uint32_t*)(levelFile - 4))[0];
}

class LevelLoader
{
private:
    Level *level;
    
public:
    LevelLoader(const char *path);
    LevelLoader(Level *level);
    
    Level *buildLevel();
    void saveFile(const char *path);
};

extern Level *loadLevel(const char* path, int w, int h);

#endif /* LevelLoader_hpp */
