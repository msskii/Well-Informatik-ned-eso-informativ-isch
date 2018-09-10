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

typedef struct filedata
{
    uint8_t *data;
    size_t filesize;
    
    inline uint8_t operator[] (int index) { return data[index]; } // Keep backwards compability
} filedata;

extern filedata readFile(const char *filePath);
extern void writeFile(const char *filePath, uint8_t *dataToWrite, int size);

#endif /* FileReader_hpp */
