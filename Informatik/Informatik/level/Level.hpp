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
#include "../entity/Player.hpp"
#include <stdint.h>

class Player;

class Level
{
private:
    Tile *tiles;
    
    
    void loadFromData(uint8_t *bytes);
    uint8_t *serialize();
public:
    Player *player;
    int width, height;
    
    inline Tile &operator[](int index) { return tiles[index]; }
    
    Tile getTile(int screenX, int screenY);
    
    Level(int w, int h);
    Level(const char *filePath); // Load from file?
    
    void render(SDL_Renderer *renderer);
};

#endif /* Level_hpp */
