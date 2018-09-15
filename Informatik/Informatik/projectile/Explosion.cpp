//
//  Explosion.cpp
//  Informatik
//
//  Created by Aaron Hodel on 15.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Explosion.hpp"
#include "../level/Level.hpp"

Explosion::Explosion(float x, float y, float explosionStrength) : Projectile(x, y, 0), strength(explosionStrength)
{
    maxRadius = explosionStrength;
    surface = IMG_Load(GET_TEXTURE_PATH("projectiles/arrow_ur")); // Same as other arrow
    velocity = {0, 0};
}

void Explosion::update(const uint8_t *keys)
{
    // Strength is time & radius from the inside that is clear
    if(strength-- < 0)
    {
        level->removeEntity(this);
    }
    else
    {
        
    }
}
