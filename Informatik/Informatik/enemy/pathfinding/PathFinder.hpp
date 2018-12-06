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
typedef vector2d (*pathfindAlg)(Tile *currentTiles, int startIndex, int endIndex);
extern uint32_t level_width, level_height;

static const vector2d VEC_UP {0, -1};
static const vector2d VEC_DOWN {0, 1};
static const vector2d VEC_LEFT {-1, 0};
static const vector2d VEC_RIGHT {1, 0};

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
    vector2d getStep(int si, int ei);
    vector2d getStep(int xs, int ys, int xe, int ye);
    vector2d getStep(float xs, float ys, float xe, float ye);
    DIRECTION getSingleDirection(float xs, float ys, float xe, float ye, float w, float h);
    vector2d getAverageDirection(float xs, float ys, float xe, float ye, float w, float h);
};

#endif /* PathFinder_hpp */
