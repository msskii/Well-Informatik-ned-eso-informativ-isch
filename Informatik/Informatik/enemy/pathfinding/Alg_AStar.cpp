//
//  Alg_AStar.cpp
//  Informatik
//
//  Created by Aaron Hodel on 15.11.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Alg_AStar.hpp"

#define CANSTEPON(index) (tiles[index].data.tileZ == tiles[startIndex].data.tileZ && tiles[index].Tile_surface != nullptr)

uint32_t scoreSize = 0;
int *gScores = nullptr;
int *fScores = nullptr;
int *cameFrom = nullptr;

void astar_init(Level *level)
{
    if(gScores != nullptr) free(gScores);
    if(fScores != nullptr) free(fScores);
    if(cameFrom != nullptr) free(cameFrom);
    scoreSize = sizeof(int) * level->width * level->height;
    level_width = level->width;
    level_height = level->height;
    gScores = (int*) malloc(sizeof(int) * level->width * level->height);
    fScores = (int*) malloc(sizeof(int) * level->width * level->height);
    cameFrom = (int*) malloc(sizeof(int) * level->width * level->height);
}

int estimateCost(int si, int ei) // Estimate the cost of getting from point a to point b (Using some pythagoras; In reality a + b would be better I think (because we can only move straight and not in diagonals)?)
{
    int sx = si % level_width;
    int sy = si / level_width;
    int ex = ei % level_width;
    int ey = ei / level_width;
    
    // return abs(sx - ex) + abs(sy - ey);
    return (sx - ex) * (sx - ex) + (sy - ey) * (sy - ey);
}

vector2d astar_step(Tile *tiles, int startIndex, int endIndex)
{    
    std::vector<int> closedSet; // Visited fields stored in here
    std::vector<int> openSet; // Possible next steps in here
    
    memset(gScores, -1, scoreSize); // Set all g-Scores to the max
    memset(fScores, -1, scoreSize); // Set all f-Scores to the max
    
    gScores[startIndex] = 0; // We don't need any cost to go from where we are to where we are
    fScores[startIndex] = estimateCost(startIndex, endIndex); // fScores is the sum of the gScore (How long we need to go there) and some estimate to how much we will need to get to the end

    std::vector<int> neighbours; // Where we store our neighbours later
    
    openSet.push_back(startIndex); // Only this field can be accessed in the beginning
    while(openSet.size() > 0) // As long as we have fields to visit
    {
        // Get the node with the lowest fScore from the open set
        int current = 0, currentIndex = 0;
        int32_t minScore = -1;
        for(size_t i = 0; i < openSet.size(); i++)
        {
            if(fScores[openSet[i]] < minScore)
            {
                minScore = fScores[openSet[i]];
                current = openSet[i];
                currentIndex = (int) i;
            }
        }
        
        if(current == endIndex) // We reached the goal in the (possible) shortest way
        {
            int lastStep = current, currentStep = current;
            while(currentStep != startIndex)
            {
                lastStep = currentStep;
                currentStep = cameFrom[currentStep];
            }

            int diff = lastStep - startIndex;
            
            if(-diff == level_width) return VEC_UP;
            else if(diff == level_width) return VEC_DOWN;
            else if(diff == -1) return VEC_LEFT;
            else if(diff == 1) return VEC_RIGHT;
            else if(diff == 1 - level_width) return VEC_UPRIGHT;
            else if(diff == -1 - level_width) return VEC_UPLEFT;
            else if(diff == 1 + level_width) return VEC_DOWNRIGHT;
            else if(diff == -1 + level_width) return VEC_DOWNLEFT;

            return VEC_UP;
        }
        
        openSet.erase(openSet.begin() + currentIndex); // we stepped on the field, so it is not open anymore
        closedSet.push_back(current); // We have visited this field
        
        // Check possible neighbours
        if(current % level_width > 0 && CANSTEPON(current - 1)) neighbours.push_back(current - 1);
        if(current / level_width > 0 && CANSTEPON(current - level_width)) neighbours.push_back(current - level_width);
        if(current % level_width < level_width - 1 && CANSTEPON(current + 1)) neighbours.push_back(current + 1);
        if(current / level_width < level_height - 1 && CANSTEPON(current + level_width)) neighbours.push_back(current + level_width);
        
        if(current % level_width > 0 && current / level_width > 0 && CANSTEPON(current - 1 - level_width)) neighbours.push_back(current - 1 - level_width);
        if(current % level_width < level_width - 1 && current / level_width > 0 && CANSTEPON(current - level_width - 1)) neighbours.push_back(current - level_width - 1);
        if(current % level_width < level_width - 1 && current / level_width < level_height - 1 && CANSTEPON(current + 1 + level_width)) neighbours.push_back(current + 1 + level_width);
        if(current % level_width > 0 && current / level_width < level_height - 1 && CANSTEPON(current - 1 + level_width)) neighbours.push_back(current - 1 + level_width);

        while(neighbours.size() > 0)
        {
            int neighbour = *neighbours.begin(); // The current neighbour
            neighbours.erase(neighbours.begin());
            
            if(std::find(closedSet.begin(), closedSet.end(), neighbour) != closedSet.end()) continue; // If the neighbour is in the closed set, we where already there
            int32_t gScore = gScores[current] + 1;
            
            if(std::find(openSet.begin(), openSet.end(), neighbour) == openSet.end()) openSet.push_back(neighbour); // New field discovered
            else if(gScore > gScores[neighbour]) continue; // Already discovered & was a better path there
            
            cameFrom[neighbour] = current;
            gScores[neighbour] = gScore;
            fScores[neighbour] = gScore + estimateCost(neighbour, endIndex);
        }
    }
    
    return VEC_UP;
}
