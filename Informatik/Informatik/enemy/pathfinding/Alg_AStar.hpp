//
//  Alg_AStar.hpp
//  Informatik
//
//  Created by Aaron Hodel on 15.11.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Alg_AStar_hpp
#define Alg_AStar_hpp

#include "PathFinder.hpp"

extern int *fScores, *gScores;

extern void astar_init(Level *level);
extern DIRECTION astar_step(Tile *tiles, int startIndex, int endIndex);

static const pathfindAlgorithm astar = {astar_init, astar_step};

#endif /* Alg_AStar_hpp */
