//
//  Enemy.hpp
//  Informatik
//
//  Created by Aaron Hodel on 04.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "../entity/Entity.hpp"
#include <vector>

enum ATTACK_STATE
{
    READY_TO_ATTACK,
    ATTACKING,
    ATTACK_DONE,
    RECHARGING
};

class Enemy;
typedef void (*attackFunction)(Enemy *e, Level *level);

class Enemy : public Entity
{
protected:
    std::vector<attackFunction> attacks;
    ATTACK_STATE attackState = READY_TO_ATTACK;
    float xdirection = 0;
    float ydirection = 0;
    int leftToMove = 0;
    bool knockbackEnabled = true;
    
public:
    virtual int checkForDamage(float x, float y) = 0; //gives player cords, every entety returns active damage as an int
    virtual void onDamage(float amount) = 0;
    virtual float onDamaging() = 0;
    int stunnedDuration = 0;
    
    //update core enemy functions
    void updateEnemey();
    
    float animationHealth = data.currentHealth; // Start without animation
    float agroRadius = TILE_SIZE * 5; // Enemy may attack in a range of x
    bool isAlive = true;
        
    void renderHP(float xoffset, float yoffset);
    void takeDamage(float amount);
};

#include "../level/Level.hpp"

#endif /* Enemy_hpp */
