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
    
    uint8_t flags = data[0];
    data++;
    float walking_speed = ((float*) data)[0];
    data += 4;
    uint32_t pathlength = ((uint32_t*)data)[0];
    data += 4;
    uint32_t *path = (uint32_t*) malloc(2 * sizeof(uint32_t) * pathlength);
    memcpy(path, data, pathlength * sizeof(uint32_t) * 2);
    
    return npc;
}
