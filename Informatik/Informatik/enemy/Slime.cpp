//
//  Slime.cpp
//  Informatik
//
//  Created by Aaron Hodel on 04.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Slime.hpp"

Slime::Slime(float x, float y, int level)
{
    data.x_pos = x;
    data.y_pos = y;
    data.speed = 2 + level / 20.0f;
    data.damage = 5.0f * level;
    data.maxhealth = 1.0f * level;
    data.currentHealth = 1.0f * level;
    animationHealth = 1.0f * level;
    agroRadius = 15 * TILE_SIZE;
    
    if(level < 10)
    {
         enemy_surface = IMG_Load(GET_TEXTURE_PATH("enemies/Enemy_GreenSlime"));
    }
    else if (level < 20)
    {
         enemy_surface = IMG_Load(GET_TEXTURE_PATH("enemies/Enemy_BlueSlime"));
    }
    else if (level < 30)
    {
        enemy_surface = IMG_Load(GET_TEXTURE_PATH("enemies/Enemy_OrangeSlime"));
    }
    else
    {
        enemy_surface = IMG_Load(GET_TEXTURE_PATH("enemies/Enemy_RedSlime"));
    }
   
    texture = getTexture(enemy_surface);
    
    SDL_Surface *hurt_surface = SDL_CreateRGBSurfaceWithFormatFrom(enemy_surface->pixels, enemy_surface->w, enemy_surface->h, 32, enemy_surface->pitch, SDL_PIXELFORMAT_ARGB8888);
    
    uint32_t *pixels = (uint32_t*) hurt_surface->pixels;
    for(int i = 0; i < enemy_surface->w * enemy_surface->h; i++)
    {
        uint32_t cp = ((uint32_t*) enemy_surface->pixels)[i];
        pixels[i] = (cp & 0xFF000000) == 0 ? 0x00FFFFFF : 0xFFFF0000 | (cp & 0xFF00);
    }
    
    texture_hurt = getTexture(hurt_surface);
}

bool Slime::isInside(float x, float y)
{
    return x >= data.x_pos && y >= data.y_pos && x <= data.x_pos + data.width && y <= data.y_pos + data.height;
}

void Slime::onAddToLevel(Level *level) {}

void Slime::render(int xoff, int yoff)
{
    renderHP((float) xoff, (float)yoff); // Render the hp of the enemy
    
    // TODO implement death animation
    
    SDL_Rect src = {32 * anim, set * 32, 32, 32};
    SDL_Rect dst = getBoundingBox();
    TRANSFORM_LEVEL_POS(dst, xoff, yoff); // Transform r to the level position
    if((hurt--) > 0)
    {
        renderWithShading(texture_hurt, src, dst);
    }
    else
    {
        renderWithShading(texture, src, dst);
    }
}

void Slime::onDamage(float amount)
{
    hurt = 10;
    
}

float Slime::onDamaging()
{
    return data.damage;
    
}

void Slime::update(const uint8_t *keys)
{
    if((attackState == ATTACKING || attackState == READY_TO_ATTACK) && (timer++) >= 5)
    {
        timer = 0;
        anim = (anim + 1) % 10;
    }
    
    if(!isAlive) return; // Dont move when dead
    
    float l = PLAYER_DIST(this, level->getPlayer());
    if(l < agroRadius && l > TILE_SIZE/4 && (attackState != ATTACK_DONE || attackState != RECHARGING))
    {
        attackState = ATTACKING;
        set = 1;
        if(anim > 2 && anim < 7)
        {
            xdirection = (level->getPlayer()->data.x_pos - this->data.x_pos)/l;
            ydirection = (level->getPlayer()->data.y_pos - this->data.y_pos)/l;
            data.dx = xdirection * data.speed * 2;
            data.dy = ydirection * data.speed * 2;
            correctMovement(data.dx, data.dy);
            data.x_pos += data.dx;
            data.y_pos += data.dy;
        }
        
    }
    else
    {
        set = 0;
        attackState = READY_TO_ATTACK;
    }
    
}
