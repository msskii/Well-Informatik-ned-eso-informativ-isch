//
//  Player.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "../config.h"
#include "../level/Level.hpp"

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50
#define PLAYER_OFFSET_X ((GAME_WIDTH + PLAYER_WIDTH) / 2)
#define PLAYER_OFFSET_Y ((GAME_HEIGHT + PLAYER_HEIGHT) / 2)

#ifdef __APPLE__
#  include <SDL2/SDL.h> // Other path than on windows
#else
#  include <SDL2.h>
#endif

class Level;

class Player
{
private:
    
public:
    float _x = 0, _y = 0; // Coordinates
    int _z = 0;// Height level
    bool inControl = true; // Player can control himself by default
    
    
    void updateMovement(float dx, float dy);
    void correctMovement(float &dx, float &dy);
    bool isInside(float dx, float dy);
    
    Level *level;
    
    Player(Level *level);
    
    void render(SDL_Renderer *renderer, int xoff, int yoff);
    
};

#endif /* Player_hpp */
