//
//  FileReader.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef FileReader_hpp
#define FileReader_hpp

#include <stdint.h>
#include "Logger.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <dirent.h> // TODO: Find alternative for windows (or include binaries for dirent)

#define TEXTURE_PATH std::string("assets/textures/")
#define FONT_PATH std::string("assets/fonts/")
#define LEVEL_PATH std::string("assets/data/")
#define LANGUAGE_PATH std::string("assets/data/lang/")
#define AUDIO_PATH std::string("assets/music/")

#define GET_VARIANT_PATH(texture_name, variant_num) (TEXTURE_PATH + texture_name + std::to_string(variant_num) + ".png").c_str()
#define GET_TEXTURE_PATH(texture_name) (TEXTURE_PATH + texture_name + ".png").c_str()
#define GET_FILE_PATH(initpath, filename) (initpath + filename).c_str()

typedef struct filedata
{
    uint8_t *data;
    size_t filesize;
    
    inline uint8_t operator[] (int index) { return data[index]; } // Keep backwards compability
} filedata;

extern filedata readFile(const char *filePath);
extern void writeFile(const char *filePath, uint8_t *dataToWrite, int size);
extern std::vector<std::string> listFiles(std::string dir);

#endif /* FileReader_hpp */
