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

#include "../items/Item.hpp"

#include "../util/SDL_Util.hpp"

class Level;

class Player
{
private:
    SDL_Surface *player_surface = nullptr;
    SDL_Texture *texture = nullptr;
    
    float _x = 0, _y = 0; // Coordinates

public:
    //stats
    bool isAlive = false;
    float currentHealth = 100, maxHealth = 100, mana = 10, maxMana = 10;
    float animationHealth = currentHealth;
    float gracePeriode = 3;
    int graceLeft = 0;
    
    // Items
    std::map<int, InventoryElement> playerItems;
    
    // Position
    float x_pos = 0, y_pos = 0;
    int xoff = 0, yoff = 0;
    uint8_t _z = 0; // Height level
    
    // Movement & control
    bool inControl = true; // Player can control himself by default
    bool actionPressed = false; // If the action key was pressed
    DIRECTION direction = DOWN;
    
    // Animation stuff
    bool walking = false;
    int anim = 0, timer = 0;
    
    inline int getOffsetX() { return -(int)_x; }
    inline int getOffsetY() { return -(int)_y; }

    void updateMovement(float dx, float dy);
    void correctMovement(float &dx, float &dy);
    bool isInside(float dx, float dy);
    void takeDamage(float amount);
    
    Level *level;
    
    Player(Level *level);
    
    void render(SDL_Renderer *renderer, int xoff, int yoff);
    void renderStats(SDL_Renderer *renderer, int xoff, int yoff);
    
};


#endif /* Player_hpp */
