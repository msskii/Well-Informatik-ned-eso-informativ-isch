//
//  Level.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Level_hpp
#define Level_hpp

#include "Tile.hpp"
#include "Event.hpp"
#include "../entity/Player.hpp"
#include <stdint.h>
#include <vector>

class Player;

class Level
{
private:
public:
    Player *player; // The player in this level
    uint32_t width, height; // 4 byte integers --> normal ints on most platforms
    std::vector<Event> events; // The events in this level
    Tile *tiles; // The tiles

public:
    Tile getTile(int xcoord, int ycoord);
    
    Level(int w, int h);
    
    void render(SDL_Renderer *renderer);
};

#endif /* Level_hpp */
