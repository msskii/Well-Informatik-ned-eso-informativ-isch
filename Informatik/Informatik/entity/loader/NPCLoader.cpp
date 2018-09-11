//
//  NPCLoader.cpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "NPCLoader.hpp"

std::vector<Entity*> Loader::loadNPCs(const char *filepath)
{
    std::vector<Entity*> npcs;
    uint8_t *data = readFile(filepath).data;
    
    int numNPCS = ((uint32_t*)data)[0];
    data += 4;
    
    for(int i = 0; i < numNPCS; i++) npcs.push_back(loadNPC(data));
    return npcs;
}

Entity* Loader::loadNPC(uint8_t *&data)
{
    float x = ((float*) data)[0];
    float y = ((float*) data)[1];
    uint32_t z = ((uint32_t*) data)[2];
    float w = ((float*) data)[3];
    float h = ((float*) data)[4];
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
    
    std::vector<NPCText> texts;
    for(uint32_t i = 0; i < numTexts; i++)
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
        
        texts.push_back({timesDisplayed, event_to_trigger, text});
    }
    
    NPC *npc = new NPC(x, y, z);
    
    if(flags)
    {
        
    }
    
    npc->texts = texts;
    npc->walking_speed = walking_speed;
    npc->data.width = w;
    npc->data.height = h;
    
    return npc;
}
