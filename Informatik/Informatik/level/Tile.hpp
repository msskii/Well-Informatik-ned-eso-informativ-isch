//
//  Tile.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#define TILE_SIZE 50

#ifdef __APPLE__
#  include <SDL2/SDL.h> // Other path than on windows
#else
#  include <SDL2.h>
#endif

class Tile
{
private:
    int xcoord, ycoord;
    
public:
    Tile();
    Tile(int x, int y);
    
    int tileNumber = 0xFFFF00FF; // Number of tile --> look on tilemap
    int tileZ = 0; // The height of this tile
    
    void render(SDL_Renderer *renderer, int xoff, int yoff);
};

struct SerializedTile
{
    int tileNumber;
    int tileZ;
};

#endif /* Tile_hpp */
