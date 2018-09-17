//
//  Explosion.hpp
//  Informatik
//
//  Created by Aaron Hodel on 15.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Explosion_hpp
#define Explosion_hpp

#include "Projectile.hpp"

class Explosion : public Projectile
{
private:
    float strength = 0;
    float maxRadius = 0;
    
public:
    Explosion(float x, float y, float explosionStrength);
    void update(const uint8_t *keys) override;
};

#endif /* Explosion_hpp */
