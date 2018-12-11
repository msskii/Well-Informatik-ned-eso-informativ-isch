//
//  PathFinder.cpp
//  Informatik
//
//  Created by Aaron Hodel on 15.11.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "PathFinder.hpp"

uint32_t level_width = 0, level_height = 0;

PathFinder::PathFinder(Level *lvl, pathfindAlgorithm alg) : level(lvl), algorithm(alg)
{
    algorithm.initFunc(lvl);
}

vector2d PathFinder::getStep(int si, int ei)
{
    return algorithm.calcFunc(level->tiles, si, ei);
}


vector2d PathFinder::getStep(int xs, int ys, int xe, int ye)
{
    return algorithm.calcFunc(level->tiles, (xs + ys * level->width) / TILE_SIZE, (xe + ye * level->width) / TILE_SIZE);
}

vector2d PathFinder::getStep(float xs, float ys, float xe, float ye)
{
    //return algorithm.calcFunc(level->tiles, (int) ((xs + TILE_SIZE / 2.0) / TILE_SIZE + (int) ((ys + TILE_SIZE / 2.0) / TILE_SIZE) * level->width), (int) ((xe + TILE_SIZE / 2.0) / TILE_SIZE + (int)((ye + TILE_SIZE / 2.0) / TILE_SIZE) * level->width));
    return algorithm.calcFunc(level->tiles, (int) (xs / TILE_SIZE + (int) (ys / TILE_SIZE) * level->width), (int) (xe / TILE_SIZE + (int)(ye / TILE_SIZE) * level->width));
}

DIRECTION PathFinder::getSingleDirection(float xs, float ys, float xe, float ye, float w, float h)
{
    vector2d dir = {0, 0};
    for(int i = 0; i < 4; i++)
    {
        vector2d bd = getStep(xs + (i % 2) * w, ys + (i / 2) * h, xe, ye);
        dir += bd;
    }
    
    if(dir.x == 0)
    {
        return dir.y >= 0.0 ? DOWN : UP;
    }
    else if(dir.y == 0)
    {
        return dir.x >= 0.0 ? RIGHT : LEFT;
    }
    else if(abs(dir.x) > abs(dir.y))
    {
        return dir.x >= 0.0 ? RIGHT : LEFT;
    }
    else if(abs(dir.y) > abs(dir.x))
    {
        return dir.y >= 0.0 ? DOWN : UP;
    }
    
    return UP;
}

vector2d PathFinder::getAverageDirection(float xs, float ys, float xe, float ye, float w, float h)
{
    /**vector2d dir = {0, 0};
    for(int i = 0; i < 4; i++)
    {
        vector2d bd = getStep(xs + (i % 2) * w, ys + (i / 2) * h, xe, ye);
        dir += bd;
    }*/
    vector2d dir = getStep(xs + w / 2.0, ys + h / 2.0, xe, ye);
    return dir;
}
