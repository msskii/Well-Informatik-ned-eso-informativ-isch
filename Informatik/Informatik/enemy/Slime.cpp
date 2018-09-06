//
//  Slime.cpp
//  Informatik
//
//  Created by Aaron Hodel on 04.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Slime.hpp"

Slime::Slime(float x, float y)
{
    data.x_pos = x;
    data.y_pos = y;
    
    enemy_surface = IMG_Load(GET_TEXTURE_PATH("enemies/Enemy_BlueSlime"));
}

bool Slime::isInside(float x, float y)
{
    return x >= data.x_pos && y >= data.y_pos && x <= data.x_pos + data.width && y <= data.y_pos + data.height;
}

void Slime::onAddToLevel(Level *level) {}

void Slime::render(SDL_Renderer *renderer, int xoff, int yoff)
{
    renderHP(renderer, xoff, yoff); // Render the hp of the enemy
    
    float l = PLAYER_DIST(this, level->player);

    if(l < attackRadius && attackState == READY_TO_ATTACK)
    {
        attackState = ATTACKING;
    }
    
    if(attackState == ATTACKING && (timer++) >= 5) // Attacking is a number... do you mean to check if the state is equal?
    {
        timer = 0;
        anim = (anim + 1) % 10;
    }
    
    if(texture == nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, enemy_surface);
        return;
    }
    
    SDL_Rect src = {32 * anim, 0, 32, 32};
    SDL_Rect dst = getBoundingBox();
    TRANSFORM_LEVEL_POS(dst, xoff, yoff); // Transform r to the level position
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void Slime::onDamage(float amount)
{
    
}

void Slime::update(const uint8_t *keys) {}
