//
//  NPCLoader.cpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "NPCLoader.hpp"

std::vector<Entity*> loadNPCs(const char *filepath)
{
    std::vector<Entity*> npcs;
    uint8_t *data = readFile(filepath);
    
    int numNPCS = ((uint32_t*)data)[0];
    data += 4;
    
    for(int i = 0; i < numNPCS; i++) npcs.push_back(loadNPC(data));
    return npcs;
}

Entity* loadNPC(uint8_t *&data)
{
    NPC *npc = new NPC(0, 0, 0);
    
    float x = ((float*) data)[0];
    float y = ((float*) data)[1];
    float w = ((float*) data)[2];
    float h = ((float*) data)[3];
    data += 16;
    
    printf("X: %f, Y: %f, W: %f, H: %f\n", x, y, w, h);
    
    uint8_t flags = data[0];
    data++;
    float walking_speed = ((float*) data)[0];
    data += 4;
    
    uint32_t pathlength = ((uint32_t*)data)[0];
    data += 4;
    uint32_t *path = (uint32_t*) malloc(2 * sizeof(uint32_t) * pathlength);
    memcpy(path, data, pathlength * sizeof(uint32_t) * 2); // Copy all the path coordinates into a path array
    data += pathlength * sizeof(uint32_t) * 2;
    
    uint32_t numTexts = ((uint32_t*)data)[0];
    data += 4;
    printf("Number of texts: %d\n", numTexts);
    
    std::vector<char *> texts;
    for(int i = 0; i < numTexts; i++)
    {
        uint32_t timesDisplayed = ((uint32_t*)data)[0];
        uint32_t event_to_trigger = ((uint32_t*)data)[1];
        uint32_t text_length = ((uint32_t*)data)[2];

        data += 12;
        
        char * text = (char*) malloc(text_length + 1);
        memcpy(text, data, text_length);
        text[text_length] = 0;
        data += text_length;
        printf("Text nr. %d with length %d: %s\n", i, text_length, text);
        texts.push_back(text);
    }
    
    return npc;
}
