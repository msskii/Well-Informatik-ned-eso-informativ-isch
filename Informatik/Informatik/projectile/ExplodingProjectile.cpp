//
//  ExplodingProjectile.cpp
//  Informatik
//
//  Created by Aaron Hodel on 10.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "ExplodingProjectile.hpp"
#include "../level/Level.hpp"
#include "../graphics/overlay/light/LightSource.hpp"

ExplodingProjectile::ExplodingProjectile(EXPLODING_TYPE type, float x, float y, float ra) : Projectile(x, y, ra)
{
    
    acceleration = velocity * (-1.0f / 60.0f);
    switch (type)
    {
        case NORMAL:
            surface = IMG_Load(GET_TEXTURE_PATH("projectiles/arrow_ur")); // Same as other arrow
            break;
        default:
            printf("No texture for this projectile...\n");
            break;
    }
}

void ExplodingProjectile::update(const uint8_t *keys)
{
    Projectile::update(keys); // Call super class
    
    velocity += acceleration;
    if(velocity.len() <= 0.5)
    {
        // level->addEntity(new FireEntity());
        level->addEntity(new Explosion(data.x_pos, data.y_pos, 3 * 60));
        level->removeEntity(this);
    }
}
