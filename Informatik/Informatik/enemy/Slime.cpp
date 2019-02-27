//
//  Slime.cpp
//  Informatik
//
//  Created by Aaron Hodel on 04.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Slime.hpp"
//#include "../entity/decorativeEntities/DamageNumber.hpp"

#define HURT_DURATION 10


Slime::Slime(float x, float y, int level)
{
    data.width = 64;
    data.height = 64;
    data.x_pos = x;
    data.y_pos = y;
    data.speed = 5 + level / 5.0f;
    data.damage = 1.0f + 0.5f * level;
    data.maxhealth = 1.0f * level;
    data.currentHealth = 1.0f * level;
    animationHealth = 1.0f * level;
    agroRadius = 15 * TILE_SIZE;
    enemy_level = level;
    
    enemy_surface = IMG_Load(GET_TEXTURE_PATH("enemies/Enemy_BlueSlime"));
    SDL_PixelFormat *fmt = enemy_surface->format;
    if(level < 10)
    {
        uint32_t *pixels = (uint32_t*) enemy_surface->pixels;
        for(int i = 0; i < enemy_surface->w * enemy_surface->h; i++)
        {
            Uint32 temp;
            temp = (pixels[i] & fmt->Amask) | (((pixels[i] & fmt->Bmask) >> fmt->Bshift) << fmt->Gshift);
            pixels[i] = temp;
        }
    }
    else if (level < 20)
    {
    
    }
    else
    {
        uint32_t *pixels = (uint32_t*) enemy_surface->pixels;
        for(int i = 0; i < enemy_surface->w * enemy_surface->h; i++)
        {
            Uint32 temp;
            temp = (pixels[i] & fmt->Amask) | (((pixels[i] & fmt->Bmask) >> fmt->Bshift) << fmt->Rshift);
            pixels[i] = temp;
        }
    }
            
    hurt_surface = SDL_CreateRGBSurfaceWithFormat(0, enemy_surface->w, enemy_surface->h, 32, SDL_PIXELFORMAT_ARGB8888);
    SDL_BlitSurface(enemy_surface, NULL, hurt_surface, NULL);
    
    uint32_t *pixels = (uint32_t*) hurt_surface->pixels;
    for(int i = 0; i < enemy_surface->w * enemy_surface->h; i++)
    {
        uint32_t cp = ((uint32_t*) hurt_surface->pixels)[i];
        pixels[i] = (cp & 0xFF000000) == 0 ? 0x00FFFFFF : 0xFFFF0000;
    }
}

int Slime::checkForDamage(float x, float y)
{
    //check if it damages it
    if (x >= data.x_pos && y >= data.y_pos && x <= data.x_pos + data.width && y <= data.y_pos + data.height)
    {
        //bounce back
        if (attackState == ATTACKING)
        {
            movementVector.clear();
            std::vector<float> tempMovement;
            tempMovement.push_back(xdirection * data.speed * -0.25f);
            tempMovement.push_back(ydirection * data.speed * -0.25f);
            for (int i = 0; i < 20;  i++) {
                movementVector.push_back(tempMovement);
            }
            tempMovement[0] = 0.0;
            tempMovement[1] = 0.0;
            
            for (int i = 0; i < 10; i++) {
                movementVector.push_back(tempMovement);
            }
            
            
        }
        return (int) data.damage;
    }
    
    return 0;
}

void Slime::onAddToLevel(Level *level) {}

void Slime::render(int xoff, int yoff)
{
    if(texture.id == 0) texture = getTexture(enemy_surface); // On main thread...
    if(texture_hurt.id == 0) texture_hurt = getTexture(hurt_surface);
    
    renderHP((float) xoff, (float)yoff); // Render the hp of the enemy
    
    // TODO implement death animation
    
    SDL_Rect src = {32 * anim, set * 32, 32, 32};
    SDL_Rect dst = {(int) data.x_pos, (int) data.y_pos, 64, 64};
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
    hurt = HURT_DURATION;
    underAttack = 600;
    DamageNumber *dmgnmbr = new DamageNumber(data.x_pos, data.y_pos, int(amount));
    level->addEntity(dmgnmbr);
    
    
}

float Slime::onDamaging()
{
        return data.damage;
    
}

void Slime::update(const uint8_t *keys)
{
    if((timer++) >= 6)
    {
        timer = 0;
        anim = (anim + 1) % 10;
    }
    
    if(!isAlive && !dying)
    {
        dying = true;
        anim = 0;
        set = 2;
    }
    if(dying)
    {
        if (anim == 4 && timer == 5)
        {
            //start dropping items
            int coins = rand() % ((enemy_level / 5) + 1) + rand() % 2;
            for (int i = 0; i < coins; i++) {
                level->addEntity(new EntityItem(data.x_pos + 32, data.y_pos + 20, "coin", rand() % 7 - 3.0f, 10.0f));
            }
            int drops = rand() % ((enemy_level / 5) + 1) + rand() % 2;
            for (int i = 0; i < drops; i++) {
                level->addEntity(new EntityItem(data.x_pos + 32, data.y_pos + 20, "glob_of_slime", rand() % 10 - 5.0f, 10.0f));
            }
            int chance = rand() % 100;
            if(chance < 30) {
                level->addEntity(new EntityItem(data.x_pos + 32, data.y_pos + 20, "mana_potion", rand() % 10 - 5.0f, 10.0f));
            }
        }
        if (anim == 9 && timer == 5)
        {
            //time to die
            level->removeEntity(this);
        }
        return;
    }
    
    Player *player = level->getPlayer(data.x_pos, data.y_pos);
    if(player == nullptr) return; // No player on server
    
    float l = PLAYER_DIST(this, player);
    if(recharging > 0) {
        recharging--;
        attackState = RECHARGING;
        set = 0;
    }
    else if (stunnedDuration > 0) {
        stunnedDuration--;
        attackState = RECHARGING;
        set = 0;
    }
    else if((l < agroRadius || (underAttack-- > 0)) && l > 0  && (attackState != RECHARGING))
    {
        if (anim == 2 && timer == 0)
        {
            set = 1;
            attackState = ATTACKING;
            xdirection = 0;
            ydirection = 0;
            for(int i = 0; i < 4; i++)
            {
                //if close enough to the player directly attack him
                if(l <= 3 * TILE_SIZE || pathfinderEnabled == 0)
                {
                    xdirection += (player->data.x_pos - data.x_pos) / l;
                    ydirection += (player->data.y_pos - data.y_pos) / l;
                }
                //if not use pathfinder option
                else
                {
                    vector2d bd = level->pathfinder->getStep(this->data.x_pos + (i % 2) * this->data.width, this->data.y_pos + (i / 2) * this->data.height, player->data.x_pos, player->data.y_pos); // This might be bad?
                    float lbd = bd.len();
                    xdirection += bd.x / lbd;
                    ydirection += bd.y / lbd;
                }
            }
        }
        if (anim > 2 && anim < 7 && attackState == ATTACKING) {
            data.dx = xdirection * data.speed / 4;
            data.dy = ydirection * data.speed / 4;
            correctMovement(data.dx, data.dy);
            data.x_pos += data.dx;
            data.y_pos += data.dy;
            if (anim == 6 && timer == 5) {
                recharging = 60;
                attackState = ATTACK_DONE;
                set = 0;
            }
        }
        
    }
    else
    {
        set = 0;
        attackState = READY_TO_ATTACK;
    }
    
}
