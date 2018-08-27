//
//  Player.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Entity.hpp"
#include "../config.h"
#include "../level/Level.hpp"

#define PLAYER_WIDTH 100
#define PLAYER_HEIGHT 100
#define PLAYER_OFFSET_X ((GAME_WIDTH + PLAYER_WIDTH) / 2)
#define PLAYER_OFFSET_Y ((GAME_HEIGHT + PLAYER_HEIGHT) / 2)

#include "../util/SDL_Util.hpp"

class Level;

class Player
{
private:
    SDL_Surface *surface = nullptr;
    SDL_Texture *texture = nullptr;
    DIRECTION direction = DOWN;
    
public:
    float realPosX = 0, realPosY = 0;
    float _x = 0, _y = 0; // Coordinates
    int xoff = 0, yoff = 0;
    uint8_t _z = 0; // Height level
    bool inControl = true; // Player can control himself by default
    bool actionPressed = false; // If the action key was pressed
    
    bool walking = false;
    int anim = 0, timer = 0;
    
    void updateMovement(float dx, float dy);
    void correctMovement(float &dx, float &dy);
    bool isInside(float dx, float dy);
    
    Level *level;
    
    Player(Level *level);
    
    void render(SDL_Renderer *renderer, int xoff, int yoff);
    
};


#endif /* Player_hpp */
