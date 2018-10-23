//
//  Slime.hpp
//  Informatik
//
//  Created by Aaron Hodel on 04.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Slime_hpp
#define Slime_hpp

#include "Enemy.hpp"

class Slime : public Enemy
{
private:
    bool isMoving = false;
    SDL_Surface *enemy_surface = nullptr, *hurt_surface = nullptr;
    gl_texture texture;
    gl_texture texture_hurt;
    
public:
    int anim = 0, set = 0, timer = 0, hurt = 0, underAttack = 0;
    int enemy_level = 0;
    Slime(float x, float y, int level);
    
    bool isInside(float x, float y) override;
    void onAddToLevel(Level *level) override;
    void render(int xoff, int yoff) override;
    void update(const uint8_t *keys) override;
    void onDamage(float amount) override;
    float onDamaging() override;
};

#endif /* Slime_hpp */
