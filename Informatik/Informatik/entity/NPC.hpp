//
//  NPC.hpp
//  Informatik
//
//  Created by Keanu Gleixner on 27.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef NPC_hpp
#define NPC_hpp

#include "Entity.hpp"

class NPC
{
public:
    float xPos = 0, yPos = 0;
    int y=0;
    NPC(float xPos, float yPos, int y);
};

#endif /* NPC_hpp */
