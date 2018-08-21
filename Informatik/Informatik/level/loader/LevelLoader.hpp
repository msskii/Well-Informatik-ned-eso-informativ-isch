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
