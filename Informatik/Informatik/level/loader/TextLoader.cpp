//
//  TextLoader.cpp
//  Informatik
//
//  Created by Aaron Hodel on 27.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "TextLoader.hpp"

TextLoader::TextLoader(const char *path)
{
    uint8_t *t = readFile(path);
    uint32_t numStrings = ((uint32_t*)t)[0];
    t += 4;
    
    for(int i = 0; i < numStrings; i++)
    {
        uint32_t strlen = ((uint32_t*)t)[0];
        uint8_t *text = (uint8_t*) malloc(strlen + 1);
        memcpy(text, t + 4, strlen);
        text[strlen] = 0;
        loadedText.push_back(std::string((const char *) text));        
        t += 4 + strlen;
    }
}
