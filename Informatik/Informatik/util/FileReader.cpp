//
//  FileReader.cpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "FileReader.hpp"

uint8_t* readFile(const char *filePath)
{
    FILE *f;
    
#ifdef __APPLE__
    f = fopen(filePath, "rb"); // Apple has the insecure version here
#else
    fopen_s(f, filePath, "rb"); // Windows has secure
#endif
    
    if(f == nullptr)
    {
        ERROR("File not found");
        return nullptr; // File not found
    }
    
    fseek(f, 0, SEEK_END);
    size_t fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *data = (uint8_t *) malloc(fileSize);
    fread(data, 1, fileSize, f); // Read data
    
    return data;
}

void writeFile(const char *filePath, uint8_t *dataToWrite, int size)
{
    FILE *f;
    
#ifdef __APPLE__
    f = fopen(filePath, "wb"); // Apple has the insecure version here
#else
    fopen_s(f, filePath, "wb"); // Windows has secure
#endif
    
    if(f == nullptr)
    {
        ERROR("File not found");
        return; // File not found
    }
    
    fwrite(dataToWrite, 1, size, f); // Write data
}