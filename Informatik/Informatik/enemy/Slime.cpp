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
    data.speed = 2;
    
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
    
    if((attackState == ATTACKING || attackState == READY_TO_ATTACK) && (timer++) >= 5)
    {
        timer = 0;
        anim = (anim + 1) % 10;
    }
    
    if(texture == nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, enemy_surface);
        return;
    }
    
    SDL_Rect src = {32 * anim, set * 32, 32, 32};
    SDL_Rect dst = getBoundingBox();
    TRANSFORM_LEVEL_POS(dst, xoff, yoff); // Transform r to the level position
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void Slime::onDamage(float amount)
{
    
}

void Slime::update(const uint8_t *keys) {
    float l = PLAYER_DIST(this, level->player);
    if(l<agroRadius && l > TILE_SIZE/4 && (attackState != ATTACK_DONE || attackState != RECHARGING))
    {
        attackState = ATTACKING;
        set = 1;
        if(anim > 2 && anim < 7)
        {
            xdirection = (level->player->x_pos - this->data.x_pos)/l;
            ydirection = (level->player->y_pos - this->data.y_pos)/l;
            data.x_pos += xdirection * data.speed * 2;
            data.y_pos += ydirection * data.speed * 2;
        }
        
    }else{
        set = 0;
        attackState = READY_TO_ATTACK;
    }
    
}
