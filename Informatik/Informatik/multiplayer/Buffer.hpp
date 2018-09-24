//
//  Buffer.hpp
//  Informatik
//
//  Created by Aaron Hodel on 21.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Buffer_hpp
#define Buffer_hpp

#include <stdint.h>
#include <stdio.h>
#include <string>

namespace Multiplayer
{
    template <typename T>
    extern T read(uint8_t *&buffer);
    
    template <typename T>
    extern void write(uint8_t *&buffer, T value);
    
    extern char *readString(uint8_t *&buffer);
    extern void writeString(uint8_t *&buffer, const char *str, int len);
    
    extern void printBuffer(uint8_t *buffer, int len);
}

#endif /* Buffer_hpp */
