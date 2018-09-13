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
   
}

bool Slime::isInside(float x, float y)
{
    return x >= data.x_pos && y >= data.y_pos && x <= data.x_pos + data.width && y <= data.y_pos + data.height;
}

void Slime::onAddToLevel(Level *level) {}

void Slime::render(SDL_Renderer *renderer, int xoff, int yoff)
{
    renderHP(renderer, (float)xoff, (float)yoff); // Render the hp of the enemy
    
    if(texture == nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, enemy_surface);
        texture_hurt = SDL_CreateTexture(renderer, enemy_surface->format->format, SDL_TEXTUREACCESS_STREAMING, enemy_surface->w, enemy_surface->h);
        SDL_SetTextureBlendMode(texture_hurt, SDL_BLENDMODE_BLEND);
        
        uint32_t *pixels;
        int pitch;
        SDL_LockTexture(texture_hurt, NULL, (void**) &pixels, &pitch);
        for(int i = 0; i < enemy_surface->w * enemy_surface->h; i++)
        {
            uint32_t cp = ((uint32_t*) enemy_surface->pixels)[i];
            pixels[i] = (cp & 0xFF000000) == 0 ? 0x00FFFFFF : 0xFFFF0000 | (cp & 0xFF00);
        }
        SDL_UnlockTexture(texture_hurt);
        return;
    }
    
    // TODO implement death animation
    
    SDL_Rect src = {32 * anim, set * 32, 32, 32};
    SDL_Rect dst = getBoundingBox();
    TRANSFORM_LEVEL_POS(dst, xoff, yoff); // Transform r to the level position
    if((hurt--) > 0)
    {
        SDL_RenderCopy(renderer, texture_hurt, &src, &dst);
    }
    else
    {
        SDL_RenderCopy(renderer, texture, &src, &dst);
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
    
    float l = PLAYER_DIST(this, level->player);
    if(l < agroRadius && l > TILE_SIZE/4 && (attackState != ATTACK_DONE || attackState != RECHARGING))
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
        
    }
    else
    {
        set = 0;
        attackState = READY_TO_ATTACK;
    }
    
}
