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

enum Direction
{
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};

class LevelGen
{
public:
        
    int width, height, birthLimit, deathLimit;
    int chanceToStartAlive, numberOfSteps;
    int *map;
    int *mapEdge;
    
    //creates a cave map and saves it to the array
    LevelGen(int widthN, int heightN, int *mapN);
    int countAliveNeighbours(int *Oldmap, int x);
    void doSimulationStep();
    void mapInitialise();
    void printTest();
    bool isAWall(int direction, int x);
    int nextDirection(int direction, int x);
    void deleteBody(int x);
    
};

#endif /* LevelGen_hpp */
