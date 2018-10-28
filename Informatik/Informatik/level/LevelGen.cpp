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
#include <vector>

LevelGen::LevelGen(int widthN, int heightN, int *mapN)
{
    birthLimit = 4;
    deathLimit = 4;
    
    width = widthN;
    height = heightN;
    
    //in %
    chanceToStartAlive = 40;
    numberOfSteps = 100;
    
    map = new int[width * height];
    mapEdge = new int[width * height];
    
    mapInitialise();
    
    printTest();
    mapN = map;
}

int LevelGen::countAliveNeighbours(int *Oldmap, int x)
{
    int count = 0;
    //left and right
    for(int i = -1; i < 2; i++)
    {
        //up and down
        for(int j = -1; j < 2; j++)
        {
            if(i == 0 && j == 0) continue; // Skip over current cell
            
            int neighbour = x + i + (j * width);
            //If we're looking at the middle point
            if((x % width == 0 && i == -1) || ((x+1) % width == 0 && i == 1) || (neighbour < 0) || (neighbour >= width * height)) count += 1; // Check if out of bounds --> if yes, alive!
            else if(Oldmap[neighbour] == 1) count += 1; // Else check actual cell
        }
    }
    return count;
}

void LevelGen::doSimulationStep()
{
    int oldMap[width * height];
    std::copy(map, map + (width * height), oldMap);
    
    for(int x = 0; x < width * height; x++)
    {
        int nbs = countAliveNeighbours(oldMap, x);
        //The new value is based on our simulation rules
        //First, if a cell is alive but has too few neighbours, kill it.
        if(oldMap[x] == 1) // == 1 is theoretically unnecessary, if the only other value is 0 (And you could make it bool[] instead of int[])
        {
            //map[x] = nbs >= deathLimit; // This is how you wrote it, shouldn't it be < (or <=) deathLimit?
            map[x] = nbs < deathLimit; // How I think it should be: Survive if there are less than deathlimit neighbours
            
            /**
            if(nbs < deathLimit) map[x] = 0;
            else map[x] = 1;*/
            //Otherwise, if the cell is dead now, check if it has the right number of neighbours to be 'born'
        }
        else map[x] = nbs >= birthLimit; // Cell comes to live if we have enough neighbours
    }
}

bool LevelGen::isAWall(int direction, int x)
{
    switch (direction)
    {
        case 0:
            return (x < width || map[x-width] == 1);
        case 1:
            return ((x+1) % width == 0 || map[x+1] == 1);
        case 2:
            return ((x+width) >= height * width  || map[x+width] == 1);
        case 3:
            return (x % width == 0 || map[x-1] == 1);
        default:
            return false;
    }
}

int LevelGen::nextDirection(int direction, int x)
{
    //We follow the wall on the left side
    //so we first check if we can go left, then up ... etc
    int checkDirection;
    for(int i = 0; i < 5; i++)
    {
        checkDirection = (direction + (1 + i)) % 4;
        if(!isAWall(checkDirection, x))
        {
            return checkDirection;
        }
    }
    return -1;
}

void LevelGen::deleteBody(int x)
{
    map[x] = 1; // Clear current cell
    
    //recusivly delete all Bodies
    //first check if left is a Tile (0)
    if (x % width != 0 && map[x-1] == 0) deleteBody(x-1);
    //then check under
    if (x + width < width * height && map[x+width] == 0) deleteBody(x+width);
    //check up
    if (x >= width && map[x-width] == 0) deleteBody(x-width);
    //check right
    if ((x+1) % width != 0 && map[x+1] == 0) deleteBody(x+1);
}

void LevelGen::mapInitialise()
{
    //save a coordinate and size of every body
    std::vector<int> bodySize;
    std::vector<int> bodyCoord;
    //randomly seed the map
    for(int x = 0; x < width * height; x++)
    {
        if(rand() % 100 <= chanceToStartAlive)
        {
            map[x] = 1;
            mapEdge[x] = 0;
        }
        else
        {
            map[x] = 0;
            mapEdge[x] = 0;
        }
    }
    
    //Generator
    for (int i = 0; i < numberOfSteps; i++) doSimulationStep();
    
    //clean empty spaces
    for (int x = 0; x < height * width; x++)
    {
        //Find a Body
        if(map[x] == 0)
        {
            //if already marked search for the end of the body
            if(mapEdge[x] == 1)
            {
                while(map[x] == 0 || mapEdge[x-1] == 0) ++x;
            }
            else
            {
                //Trace the Outline of the Found body
                //Direction 0 = Up, 1 = Right, 2 = Down, Left = 3
                int direction = 0;
                int checkingX = x; // Why name it x if it actually the index?
                int count = 0;
                
                do
                {
                    mapEdge[checkingX] = 1;
                    count++;
                    //look for the next open space
                    int checkDirection;
                    for(int k = 0; k < 4; k++)
                    {
                        checkDirection = (direction + k + 3) % 4;
                        if(!isAWall(checkDirection, checkingX))
                        {
                            direction = checkDirection;
                            break; // ??? k = 5?
                        }
                    }
                    
                    switch (direction)
                    {
                        case 0:
                            checkingX -= width;
                            break;
                        case 1:
                            checkingX++;
                            break;
                        case 2:
                            checkingX += width;
                            break;
                        case 3:
                            checkingX--;
                            break;
                        default:
                            break;
                    }
                } while (checkingX != x); // WTF !(a == b)
                bodySize.push_back(count);
                bodyCoord.push_back(x);
                //goo out of the current body
                while(map[x] != 1) ++x;
            }
        }
    }
    //now get rid of smaller bodies
    int biggestBodySize = 0;
    
    for (int i = 0; i < bodyCoord.size(); i++)
    {
        if (bodySize[i] > biggestBodySize)
        {
            biggestBodySize = bodySize[i];
        }
    }
    
    for (int i = 0; i < bodyCoord.size(); i++)
    {
        if (bodySize[i] != biggestBodySize)
        {
            deleteBody(bodyCoord[i]);
        }
    }
}



void LevelGen::printTest()
{
    std::string outstring;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            outstring = map[i * width + j] ? "I" : "O"; // Ever heard of ternary operator?
            
            /**
            if(map[i * width + j] == 0)
            {
                outstring += "O";
            }
            else
            {
                outstring += "I";
            }*/
            
        }
        outstring += "\n";
    }
    std::cout << "Map: \n" << outstring;
}

