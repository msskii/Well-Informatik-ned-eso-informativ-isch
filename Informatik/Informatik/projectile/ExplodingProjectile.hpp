//
//  ExplodingProjectile.hpp
//  Informatik
//
//  Created by Aaron Hodel on 10.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef ExplodingProjectile_hpp
#define ExplodingProjectile_hpp

#include "Projectile.hpp"

enum EXPLODING_TYPE
{
    NORMAL
};

class ExplodingProjectile : public Projectile
{
public:
    vector2d acceleration;
    
    ExplodingProjectile(EXPLODING_TYPE type, float x, float y, float ra);
    void update(const uint8_t *keys) override;
};

#endif /* ExplodingProjectile_hpp */
