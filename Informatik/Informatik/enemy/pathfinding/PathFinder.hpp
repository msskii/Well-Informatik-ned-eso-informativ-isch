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

};

#endif /* PathFinder_hpp */
