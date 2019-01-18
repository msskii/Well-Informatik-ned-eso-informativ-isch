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


class Player : public Entity
{
protected:
    Player() {}
    
private:
    SDL_Surface *player_surface = nullptr;
    SDL_Surface *hurt_surface = nullptr;
    
    float _x = 0, _y = 0; // Coordinates

public:
    //stats
    bool isAlive = false;
    float currentHealth = 100, maxHealth = 100, currentMana = 100, maxMana = 100;
    float animationHealth = currentHealth, animationMana = currentMana, lastHealth = currentHealth, lastMana = currentMana;
    float manaDifference = 0, hpDifference = 0, manaBarTicks = 0, hpBarTicks = 0;
    float gracePeriode = 2;
    int graceLeft = 0;
    
    //spells & attack
    std::vector<Spell *> spells;
    uint8_t spellID1 = 1, spellID2 = 2, spellID3 = 3, spellID4 = 4;

    
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
    int anim = 0, timer = 0, animSet = 0, blinkTimer = 0, blinkDuration = 40;
    gl_texture texture;
    gl_texture texture_hurt;

    inline int getOffsetX() { return -(int)_x; }
    inline int getOffsetY() { return -(int)_y; }
    
    inline float getXInLevel() { return data.x_pos; }
    inline float getYInLevel() { return data.y_pos; }

    void updateMovement(float dx, float dy);
    void correctMovement(float &dx, float &dy);
    bool isInside(float dx, float dy);
    void checkForEntityInteraction();
    void takeDamage(float amount);
    void moveTo(float x, float y);
    void spell(int index);
    void meleeAttack();
    
    void addItem(Item* item);
    
    Level *current_level;
    
    Player(Level *level);
    
    virtual void render(int xoff, int yoff) override; // Override base class's function for this
    void renderStats(int xoff, int yoff);
    void onAddToLevel(Level *level) override {}
    void update(const uint8_t *keys) override;

};


#endif /* Player_hpp */
