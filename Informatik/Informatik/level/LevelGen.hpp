//
//  LevelGen.hpp
//  Informatik
//
//  Created by Keanu Gleixner on 25.10.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef LevelGen_hpp
#define LevelGen_hpp

#include <stdio.h>

class LevelGen{
    
    public:
        
    int width, height, birthLimit, deathLimit;
    int chanceToStartAlive, numberOfSteps;
    int *map;
    
    LevelGen();
    int countAliveNeighbours(int *Oldmap, int x);
    void doSimulationStep();
    void mapInitialise();
    void printTest();
    
};
#endif /* LevelGen_hpp */
