//
//  Alg_Line.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.11.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Alg_Line_hpp
#define Alg_Line_hpp

#include "PathFinder.hpp"

extern void line_init(Level *level);
extern vector2d line_step(Tile *tiles, int startIndex, int endIndex);

static const pathfindAlgorithm straight_line = {line_init, line_step};


#endif /* Alg_Line_hpp */
