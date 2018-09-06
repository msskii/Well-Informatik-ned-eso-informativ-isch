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
    SDL_Surface *enemy_surface = nullptr;
    SDL_Texture *texture = nullptr;
    
public:
    int anim = 0, timer = 0;
    Slime(float x, float y);
    
    bool isInside(float x, float y) override;
    void onAddToLevel(Level *level) override;
    void render(SDL_Renderer *renderer, int xoff, int yoff) override;
    void update(const uint8_t *keys) override;
    void onDamage(float amount) override;
};

#endif /* Slime_hpp */
