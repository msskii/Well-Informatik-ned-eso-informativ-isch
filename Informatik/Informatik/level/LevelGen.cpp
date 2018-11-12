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
    size = width * height;
    
    //in %
    chanceToStartAlive = 53;
    numberOfSteps = 100;
    
    map = new int[size];
    mapEdge = new int[size];
    
    mapInitialise();
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
            if((x % width == 0 && i == -1) || ((x+1) % width == 0 && i == 1) || (neighbour < 0) || (neighbour >= size)) count += 1; // Check if out of bounds --> if yes, alive!
            else if(oldmap[neighbour] == WALL) count += 1; // Else check actual cell
        }
    }
    return count;
}

void LevelGen::doSimulationStep()
{
    int *oldMap = new int[size];
	memcpy(oldMap, map, size * sizeof(int));

    for(int x = 0; x < size; x++)
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
            return ((x+width) >= size  || map[x+width] == WALL);
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
    if (x + width < size && map[x+width] == DIRT) deleteBody(x+width);
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
    for(int x = 0; x < size; x++)
    {
        mapEdge[x] = 0;
        map[x] = (rand() % 100 <= chanceToStartAlive); // Maybe add ? WALL : DIRT;
    }
    
    //Generator
    for (int i = 0; i < numberOfSteps; i++) doSimulationStep();
    //clean empty spaces
    for (int x = 0; x < size; x++)
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
    //make sure there is a wall around the whole thing
    for (int i = 0; i < width; i++)
    {
        map[i] = WALL;
        map[size - (i + 1)] = WALL;
    }
    for (int i = 0; i < height; i++)
    {
        map[i * width] = WALL;
        map[((1+i) * width) - 1] = WALL;
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
    //finaly set the entrance and exit
    //search a pattern off 3 Tiles next to a wall
    for (int i = 0;  i < size; i++)
    {
        if ((i % width < (width - 6)) && ((i + width + 6) < size) && map[i] == WALL && map[i+1] == WALL && map[i+2] == WALL && map[i+width] == DIRT && map[i+1+width] == DIRT && map[i+2+width] == DIRT)
        {
            map[i+width+1] = ENTRANCE;
            break;
        }
    }
    for (int i = size;  i > -1; i--)
    {
        if ((i % width < (width - 6)) && ((i + width + 6) < size) && map[i] == WALL && map[i+1] == WALL && map[i+2] == WALL && map[i+width] == DIRT && map[i+1+width] == DIRT && map[i+2+width] == DIRT)
        {
            map[i+width+1] = EXIT;
            break;
        }
    }
    for (int i = 0; i < size; i++) {
        if(map[i] == DIRT) amountGroundTiles++;
    }
}
void LevelGen::addGrassrec(int strength, int lastDir, int x)
{
    
    if (map[x] != WALL && map[x] != EXIT && map[x] != ENTRANCE)
    {
        map[x] = GRASS;
        int newStrength = strength - 10;
        if (rand() % 100 < strength) {
            addGrassrec(newStrength, UP, x - width);
        }
        if (rand() % 100 < strength) {
            addGrassrec(newStrength, RIGHT, x + 1);
        }
        if (rand() % 100 < strength) {
            addGrassrec(newStrength, DOWN, x + width);
        }
        if (rand() % 100 < strength) {
            addGrassrec(newStrength, LEFT, x - 1);
        }
    }
}

void LevelGen::addGrasspatch(int patchSize, int amount)
{
    //searches the right spots to add grass
    for (int i = 0; i < amount; i ++)
    {
        //try n times to find a fitting tile
        for (int j = 0; j < 50; j++) {
            //int k = rand() % size;
            int k = 510;
            if(map[k] != WALL && map[k] != EXIT && map[k] != ENTRANCE)
            {
                addGrassrec(patchSize, UP, k);
                break;
            }
        }
        
    }
    return;
}

void LevelGen::addBasicEnemies(int amount)
{
    for (int i = 0; i < size; i++)
    {
        if(map[i] == DIRT && rand() % size < amount )
        {
            map[i] = BASIC_ENEMY;
        }
    }
}

void LevelGen::returnMap(int *mapN)
{
    memcpy(mapN, map, sizeof(int) * size);
    if (debugging) {
        printTest();
    }
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
    std::cout << "Map: \n" << outstring.c_str();
    outstring = "";
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            outstring+= (char) mapEdge[i * width + j] + '0';
        }
        outstring += "\n";
    }
    std::cout << "Edge: \n" << outstring.c_str();
}

