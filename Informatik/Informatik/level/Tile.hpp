//
//  Tile.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#ifdef __APPLE__
#  include <SDL2/SDL.h> // Other path than on windows
#else
#  include <SDL2.h>
#endif

class Tile
{
private:
    int xcoord, ycoord;
    int tileNumber = 0xFFFF00FF; // Number of tile --> look on tilemap
    
public:
    Tile();
    Tile(int x, int y);
};

#endif /* Tile_hpp */
