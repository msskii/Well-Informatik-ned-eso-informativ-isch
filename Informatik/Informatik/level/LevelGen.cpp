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

LevelGen::LevelGen(int widthN, int heightN)
{
    //dead cells need so many cells around it to revive
    birthLimit = 4;
    //if a cell has less that somany cells around it, it dies
    deathLimit = 4;
    
    width = widthN;
    height = heightN;
    
    //in %
    chanceToStartAlive = 55;
    numberOfSteps = 10;
    
    map = new int[width * height];
    mapEdge = new int[width * height];
    
    mapInitialise();
    
    if (debugging) {
        printTest();
    }
    printTest();
}

int LevelGen::countAliveNeighbours(int *oldmap, int x)
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
            else if(oldmap[neighbour] == WALL) count += 1; // Else check actual cell
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
        if(oldMap[x] == WALL)
        {
            if(nbs < deathLimit) map[x] = DIRT; // If not enough neighbours, cell dies of loneliness :(
        }else if(nbs > birthLimit) map[x] = WALL;  // Cell comes to live if we have enough neighbours
    }
}

bool LevelGen::isAWall(int direction, int x)
{
    switch (direction)
    {
        case UP: // UP
            return (x < width || map[x-width] == WALL);
        case RIGHT: // RIGHT
            return ((x+1) % width == 0 || map[x+1] == WALL);
        case DOWN: // DOWN
            return ((x+width) >= height * width  || map[x+width] == WALL);
        case LEFT: // LEFT
            return (x % width == 0 || map[x-1] == WALL);
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
        if(!isAWall(checkDirection, x)) return checkDirection;
    }
    return -1;
}

void LevelGen::deleteBody(int x)
{
    map[x] = WALL; // Clear current cell
    
    //recusivly delete all Bodies
    //first check if left is a Tile (0)
    if (x % width != 0 && map[x-1] == DIRT) deleteBody(x-1);
    //then check under
    if (x + width < width * height && map[x+width] == DIRT) deleteBody(x+width);
    //check up
    if (x >= width && map[x-width] == DIRT) deleteBody(x-width);
    //check right
    if ((x+1) % width != 0 && map[x+1] == DIRT) deleteBody(x+1);
}

void LevelGen::mapInitialise()
{
    //save a coordinate and size of every body
    std::vector<int> bodySize;
    std::vector<int> bodyCoord;
    //randomly seed the map
    for(int x = 0; x < width * height; x++)
    {
        mapEdge[x] = 0;
        map[x] = (rand() % 100 <= chanceToStartAlive); // Maybe add ? WALL : DIRT;
    }
    
    //Generator
    for (int i = 0; i < numberOfSteps; i++) doSimulationStep();
    //clean empty spaces
    for (int x = 0; x < height * width; x++)
    {
        //Find a Body
        if(map[x] == DIRT)
        {
            //if already marked search for the end of the body
            if(mapEdge[x] == 1)
            {
                while(map[x] == DIRT || mapEdge[x-1] == 0) ++x;
            }
            else
            {
                //Trace the Outline of the Found body
                //Direction 0 = Up, 1 = Right, 2 = Down, Left = 3
                int direction = 0;
                int checkingX = x;
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
                            break;
                        }
                    }
                    
                    switch (direction)
                    {
                        case UP:
                            checkingX -= width;
                            break;
                        case RIGHT:
                            checkingX++;
                            break;
                        case DOWN:
                            checkingX += width;
                            break;
                        case LEFT:
                            checkingX--;
                            break;
                        default:
                            checkingX = x;
                            break;
                    }
                } while (checkingX != x);
                bodySize.push_back(count);
                bodyCoord.push_back(x);
                
                //goo out of the current body
                while(map[x] != WALL) ++x;
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
    //Invert the map so 0 is a wall and 1 is a Tile
    //finaly set the entrance
    //search a pattern off 3 Tiles next to a wall
    for (int i = 0;  i < width * height; i++)
    {
        if ((i % width < (width - 6)) && ((i + width + 6) < width * height) && map[i] == WALL && map[i+1] == WALL && map[i+2] == WALL && map[i+width] == DIRT && map[i+1+width] == DIRT && map[i+2+width] == DIRT)
        {
            map[i+width+1] = ENTRANCE;
            break;
        }
    }
}

void LevelGen::addGrasspatch(int *mapN, int strength)
{
    return;
}

void LevelGen::returnMap(int *mapN)
{
    mapN = map;
}


void LevelGen::printTest()
{
    std::string outstring;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            outstring+= (char) map[i * width + j] + '0';
        }
        outstring += "\n";
    }
    std::cout << "Map: \n" << outstring;
    outstring = "";
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            outstring+= (char) mapEdge[i * width + j] + '0';
        }
        outstring += "\n";
    }
    std::cout << "Edge: \n" << outstring;
}

