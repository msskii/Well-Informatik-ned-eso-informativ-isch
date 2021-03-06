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
#include <cstring>

#define debugging 0

class LevelGen
{

private:
    enum Direction
    {
        UP = 0,
        RIGHT = 1,
        DOWN = 2,
        LEFT = 3
    };
    
    enum Tiles
    {
        WALL = 0,
        DIRT = 1,
        ENTRANCE = 2,
        EXIT = 3,
        BASIC_ENEMY = 4,
        GRASS = 5,
    };
    
public:
    
    int width, height, birthLimit, deathLimit, size;
    int chanceToStartAlive, numberOfSteps;
    int amountGroundTiles;
    int *map;
    int *mapEdge;
    
    //creates a cave map
    LevelGen(int widthN, int heightN);
    int countAliveNeighbours(int *Oldmap, int x);
    void doSimulationStep();
    void mapInitialise();
    void printTest();
    bool isAWall(int direction, int x);
    int nextDirection(int direction, int x);
    void deleteBody(int x);
    //saves the map to the passed array
    void returnMap(int *mapN);
    
    //functions to diversivy level
    void addGrasspatch(int patchSize, int amount);
    void addGrassrec(int depth, int lastDir, int x);
    void addBasicEnemies(int amount);
    void addWater(int strength);
    void addOre(int depthLevel);
    
};

#endif /* LevelGen_hpp */
