//
//  Explosion.cpp
//  Informatik
//
//  Created by Aaron Hodel on 15.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Explosion.hpp"
#include "../level/Level.hpp"

Explosion::Explosion(float x, float y, float explosionStrength) : Projectile(x, y, (float) PI / 4.0f, PROJECTILE_ARROW), strength(explosionStrength)
{
    maxRadius = explosionStrength;
    surface = IMG_Load(GET_TEXTURE_PATH("projectiles/flame_anim")); // Same as other arrow
    texture = getTexture(surface);
    velocity = {0, 0};
    // despawnTimer = 60 * 1000;
    max_anim = 10; // 10 animations
}

void Explosion::update(const uint8_t *keys)
{
    Projectile::update(keys); // Call super class
    
    // Strength is time & radius from the inside that is clear
    /**if(strength-- < 0)
    {
        level->removeEntity(this);
    }
    else
    {
        
    }*/
}
