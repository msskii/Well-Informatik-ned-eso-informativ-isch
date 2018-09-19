//
//  Enemy.cpp
//  Informatik
//
//  Created by Aaron Hodel on 04.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Enemy.hpp"
#include "../level/Level.hpp"

void Enemy::takeDamage(float amount)
{
    data.currentHealth -= amount;
    if(data.currentHealth <= 0)
    {
        //level->removeEntity(this); // Dead
        isAlive = false;
    }
    
    if(attackState == READY_TO_ATTACK) attackState = ATTACKING;
    
    onDamage(amount);
}

#define MAX_STEP 0.05f

void Enemy::renderHP(float xoffset, float yoffset)
{
    if(animationHealth <= 0 || data.currentHealth == data.maxhealth) return; // Dead or full health
    
    if(animationHealth != data.currentHealth)
    {
        float difference = data.currentHealth - animationHealth;
        float step = difference;
        if(abs(step) >=  data.maxhealth * MAXPERCENT_PER_FRAME) step = SIGN(difference) * data.maxhealth * MAXPERCENT_PER_FRAME;
        animationHealth += step;
        
        if(animationHealth <= 0)
        {
            level->removeEntity(this);
        }
    }
    
    SDL_Rect hpbar = { (int) data.x_pos, (int) data.y_pos - 40, (int) data.width, 20 };
    TRANSFORM_LEVEL_POS(hpbar, xoffset, yoffset);
    
    //COLOR(renderer, 0xFF000000);
    //SDL_RenderFillRect(renderer, &hpbar); // Draw black border
    fillRect(0xFF000000, hpbar);
    
    // If it ever does not work: add ceil() around those four lines
    hpbar.x += (int) ceil(1.0 / SCALE_X);
    hpbar.y += (int)ceil(1.0 / SCALE_Y);
    hpbar.w -= (int)ceil(2.0 / SCALE_X);
    hpbar.h -= (int)ceil(2.0 / SCALE_Y);
    
    //COLOR(renderer, 0xFFFF0000); // Color red for depleted hp
    //SDL_RenderFillRect(renderer, &hpbar); // Full background
    fillRect(0xFFFF00, hpbar);
    
    hpbar.w = (int)(data.width * animationHealth / data.maxhealth);
    // COLOR(renderer, 0xFF00FF00);
    // SDL_RenderFillRect(renderer, &hpbar); // Draw hp in green
    // Draw box around hp bar
    fillRect(0xFFFF00, hpbar);
}
