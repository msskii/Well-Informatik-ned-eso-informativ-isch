//
//  PathFinder.hpp
//  Informatik
//
//  Created by Aaron Hodel on 15.11.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef PathFinder_hpp
#define PathFinder_hpp

#include "../../entity/Entity.hpp"
#include "../../level/Tile.hpp"
#include "../../level/Level.hpp"

typedef void (*pathfindInit)(Level *level);
typedef DIRECTION (*pathfindAlg)(Tile *currentTiles, int startIndex, int endIndex);
extern uint32_t level_width, level_height;

typedef struct pathFindAlgorithm
{
    pathfindInit initFunc;
    pathfindAlg calcFunc;
} pathfindAlgorithm;

class PathFinder
{
private:
    pathfindAlgorithm algorithm;
    Level *level = nullptr;
    
public:
    PathFinder(Level *level, pathfindAlgorithm alg);
    DIRECTION getStep(int si, int ei);
    DIRECTION getStep(int xs, int ys, int xe, int ye);
    DIRECTION getStep(float xs, float ys, float xe, float ye);
    DIRECTION getSingleDirection(float xs, float ys, float xe, float ye, float w, float h);
    vector2d getAverageDirection(float xs, float ys, float xe, float ye, float w, float h);
};

#endif /* PathFinder_hpp */
