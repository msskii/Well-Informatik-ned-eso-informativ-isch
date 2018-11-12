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
#include <cstring>

namespace Multiplayer
{
    template <typename T>
    static T read(uint8_t *&buffer)
    {
        T a = *((T*) buffer);
        buffer += sizeof(T);
        return a;
    }
    
    template <typename T>
    static void write(uint8_t *&buffer, T value)
    {
        *((T*) buffer) = value;
        buffer += sizeof(T);
    }
    
    extern char *readString(uint8_t *&buffer);
    extern void writeString(uint8_t *&buffer, const char *str, int len);
    
    extern void printBuffer(uint8_t *buffer, int len);
}

#endif /* Buffer_hpp */
