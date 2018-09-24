//
//  Buffer.cpp
//  Informatik
//
//  Created by Aaron Hodel on 21.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Buffer.hpp"

template <typename T>
T Multiplayer::read(uint8_t *&buffer)
{
    T a = ((T*) buffer)[0];
    buffer += sizeof(T);
    return a;
}

template <typename T>
void Multiplayer::write(uint8_t *&buffer, T value)
{
    *((T*) buffer) = value;
    buffer += sizeof(T);
}

char *Multiplayer::readString(uint8_t *&buffer)
{
    int length = read<int>(buffer);
    char *str = (char*) malloc(length + 1); // With null terminator
    memcpy(str, buffer, length);
    str[length] = 0;
    buffer += length;
    return str;
}

void Multiplayer::writeString(uint8_t *&buffer, const char *text, int length)
{
    write<int>(buffer, length);
    memcpy(buffer, text, length);
    buffer += length;
}

void Multiplayer::printBuffer(uint8_t *buffer, int len)
{
    printf("Buffer (Len = %d): \n", len);
    for(int i = 0; i < len; i++)
    {
        printf("\t0x%.02X\n", buffer[i]);
    }
}
