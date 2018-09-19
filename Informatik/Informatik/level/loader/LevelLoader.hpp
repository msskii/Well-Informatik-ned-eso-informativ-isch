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

#define LOADER_VERSION 3

namespace Loader
{
    template <typename T>
    extern T read(uint8_t *&levelFile);
    template <typename T>
    extern void write(uint8_t *&levelFile, T value);
    
    void writeString(uint8_t *&levelFile, const char *text, int length);
    char *readString(uint8_t *&levelFile);

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
}
    
#endif /* LevelLoader_hpp */
