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
#define pathfinderEnabled 1

class Slime : public Enemy
{
private:
    bool isMoving = false;
    SDL_Surface *enemy_surface = nullptr, *hurt_surface = nullptr;
    gl_texture texture;
    gl_texture texture_hurt;
    
public:
    int  hurt = 0, underAttack = 0, bounceBack = 0, recharging = 0;
    int enemy_level = 0;
    bool dying = false;
    Slime(float x, float y, int level);
    
    int checkForDamage(float x, float y) override;
    void onAddToLevel(Level *level) override;
    void render(int xoff, int yoff) override;
    void update(const uint8_t *keys) override;
    void onDamage(float amount) override;
    float onDamaging() override;
};

#endif /* Slime_hpp */
