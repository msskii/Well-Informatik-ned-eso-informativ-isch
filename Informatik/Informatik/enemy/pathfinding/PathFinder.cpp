//
//  PathFinder.cpp
//  Informatik
//
//  Created by Aaron Hodel on 15.11.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "PathFinder.hpp"

PathFinder::PathFinder(Level *lvl, pathfindAlgorithm alg) : level(lvl), algorithm(alg)
{
    algorithm.initFunc(lvl);
}

DIRECTION PathFinder::getStep(int si, int ei)
{
    return algorithm.calcFunc(level->tiles, si, ei);
}


DIRECTION PathFinder::getStep(int xs, int ys, int xe, int ye)
{
    return algorithm.calcFunc(level->tiles, (xs + ys * level->width) / TILE_SIZE, (xe + ye * level->width) / TILE_SIZE);
}

DIRECTION PathFinder::getStep(float xs, float ys, float xe, float ye)
{
    //return algorithm.calcFunc(level->tiles, (int) ((xs + TILE_SIZE / 2.0) / TILE_SIZE + (int) ((ys + TILE_SIZE / 2.0) / TILE_SIZE) * level->width), (int) ((xe + TILE_SIZE / 2.0) / TILE_SIZE + (int)((ye + TILE_SIZE / 2.0) / TILE_SIZE) * level->width));
    return algorithm.calcFunc(level->tiles, (int) (xs / TILE_SIZE + (int) (ys / TILE_SIZE) * level->width), (int) (xe / TILE_SIZE + (int)(ye / TILE_SIZE) * level->width));
}
