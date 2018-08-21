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

extern uint8_t* readFile(const char *filePath);
extern void writeFile(const char *filePath, uint8_t *dataToWrite, int size);

#endif /* FileReader_hpp */
