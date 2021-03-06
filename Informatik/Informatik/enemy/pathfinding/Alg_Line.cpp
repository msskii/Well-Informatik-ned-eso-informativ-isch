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

vector2d line_step(Tile *tiles, int startIndex, int endIndex)
{
    int sx = startIndex % level_width;
    int sy = startIndex / level_width;
    int ex = endIndex % level_width;
    int ey = endIndex / level_width;
    
    if(sx == ex && sy == ey) return {0, 0};
    
	vector2d v = { (float)(ex - sx), (float)(ey - sy) };
    return ((vector2d) v).norm();
}
