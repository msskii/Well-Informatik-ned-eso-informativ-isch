//
//  Alg_Line.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.11.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Alg_Line.hpp"

void line_init(Level *level)
{
    level_width = level->width;
    level_height = level->height;
}

DIRECTION line_step(Tile *tiles, int startIndex, int endIndex)
{
    int sx = startIndex % level_width;
    int sy = startIndex / level_width;
    int ex = endIndex % level_width;
    int ey = endIndex / level_width;
    
    if(abs(sx - ex) > abs(sy - ey)) return (ex - sx) > 0 ? RIGHT : LEFT;
    else return (ey - sy) > 0 ? DOWN : UP;
}
