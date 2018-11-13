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
#include <map>
#include "../config.h"
#include "../items/Item.hpp"
#include "../util/SDL_Util.hpp"
#include "../projectile/Spell.hpp"

class Level;

class Player : public Entity
{
protected:
    Player() {}
    
private:
    SDL_Surface *player_surface = nullptr;
    
    float _x = 0, _y = 0; // Coordinates

public:
    //stats
    bool isAlive = false;
    float currentHealth = 100, maxHealth = 100, mana = 10, maxMana = 10;
    float animationHealth = currentHealth;
    float gracePeriode = 3;
    int graceLeft = 0;
    
    //spells & attack
    uint8_t spellID1 = 0, spellID2 = 1, spellID3 = 2, spellID4 = 3;
    
    // Items
    std::map<int, InventoryElement> playerItems;
    
    // Position
    int xoff = 0, yoff = 0;
    uint8_t _z = 0; // Height level
    bool isBehind = false; //Is behind a building?
    
    // Movement & control
    bool inControl = true, serverPlayer = false; // Player can control himself by default
    bool actionPressed = false; // If the action key was pressed
    DIRECTION direction = DOWN;
    
    // Animation stuff
    bool walking = false;
    int anim = 0, timer = 0, animSet = 0;
    gl_texture texture;

    inline int getOffsetX() { return -(int)_x; }
    inline int getOffsetY() { return -(int)_y; }

    void updateMovement(float dx, float dy);
    void correctMovement(float &dx, float &dy);
    bool isInside(float dx, float dy);
    void takeDamage(float amount);
    void moveTo(float x, float y);
    void spell(int index);
    void meleeAttack();
    
    Level *current_level;
    
    Player(Level *level);
    
    virtual void render(int xoff, int yoff) override; // Override base class's function for this
    void renderStats(int xoff, int yoff);
    void onAddToLevel(Level *level) override {}
    void update(const uint8_t *keys) override;

};


#endif /* Player_hpp */
