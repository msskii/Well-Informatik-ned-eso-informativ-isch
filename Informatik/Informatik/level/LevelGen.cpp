//
//  LevelGen.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 25.10.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "LevelGen.hpp"
#include <fstream>
#include <iostream>

LevelGen::LevelGen(){
    birthLimit = 4;
    deathLimit = 4;
    width = 48;
    height = 48;
    //in %
    chanceToStartAlive = 40;
    numberOfSteps = 4;
    map = new int[width * height];
    mapInitialise();
    printTest();
}

int LevelGen::countAliveNeighbours(int *Oldmap, int x){
    int count = 0;
    //left and right
    for(int i=-1; i<2; i++){
        //up and down
        for(int j=-1; j<2; j++){
            int neighbour = x + i + (j * width);
            //If we're looking at the middle point
            if(i == 0 && j == 0){
                //Do nothing, we don't want to add ourselves in!
            }else if((x % width == 0 && i == -1) || ((x+1) % width == 0 && i == 1) || (neighbour < 0) || (neighbour >= width * height)){
                count += 1;
            }else if(Oldmap[neighbour] == 1){
                count += 1;
            }
        }
    }
    return count;
}

void LevelGen::doSimulationStep(){
    int oldMap[width * height];
    std::copy(map, map + (width * height), oldMap);
    for(int x=0; x < width * height; x++){
        int nbs = countAliveNeighbours(oldMap, x);
        //The new value is based on our simulation rules
        //First, if a cell is alive but has too few neighbours, kill it.
        if(oldMap[x] == 1){
            if(nbs < deathLimit){
                map[x] = 0;
            }
            else{
                map[x] = 1;
            }
            //Otherwise, if the cell is dead now, check if it has the right number of neighbours to be 'born'
        }else{
            if(nbs > birthLimit){
                map[x] = 1;
            }
            else{
                map[x] = 0;
            }
        }
    }
}

void LevelGen::mapInitialise(){
    //randomly seed the map
    for(int x=0; x<width * height; x++){
        if(rand() % 100 <= chanceToStartAlive){
            map[x] = 1;
        }else{
            map[x] = 0;
        }
    }
    
    //Generator
    for (int i = 0; i < numberOfSteps; i++) {
        doSimulationStep();
    }
}

void LevelGen::printTest(){
    std::string outstring;
    for (int i = 0; i < height; i++) {
        /*for (int j = 0; j < width; j++) {
         outstring += map[i * width + j] + '0';
         outstring += ' ';
         }*/
        
        for (int j = 0; j < width; j++) {
            if(map[i * width + j] == 0){
                outstring += "O";
            }else{
                outstring += "I";
            }
            
        }
        outstring += "\n";
    }
    std::cout << "Map: \n" << outstring;
}

