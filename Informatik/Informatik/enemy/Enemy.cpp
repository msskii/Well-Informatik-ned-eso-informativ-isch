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
        level->removeEntity(this); // Dead
    }
}

void Enemy::renderHP(SDL_Renderer *renderer, float xoffset, float yoffset)
{
    if(data.currentHealth <= 0 || data.currentHealth == data.maxhealth) return; // Dead or full health
    
    SDL_Rect hpbar = { (int) data.x_pos, (int) data.y_pos - 40, (int) data.width, 20 };
    TRANSFORM_LEVEL_POS(hpbar, xoffset, yoffset);
    
    COLOR(renderer, 0xFFFF0000); // Color red for depleted hp
    SDL_RenderFillRect(renderer, &hpbar); // Full background
    
    hpbar.w = (int)(data.width * data.currentHealth / data.maxhealth);
    COLOR(renderer, 0xFF00FF00);
    SDL_RenderFillRect(renderer, &hpbar); // Draw hp in green
    // Draw box around hp bar
    
    COLOR(renderer, 0xFF000000);
    hpbar.w = data.width - 1;
    hpbar.x += 1;
    hpbar.h -= 1;
    SDL_RenderDrawRect(renderer, &hpbar); // Draw black border
}
