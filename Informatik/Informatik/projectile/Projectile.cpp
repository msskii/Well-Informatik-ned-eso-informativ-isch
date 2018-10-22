//
//  Projectile.cpp
//  Informatik
//
//  Created by Aaron Hodel on 04.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Projectile.hpp"
#include "../level/Level.hpp"

Projectile::Projectile(float x, float y, float ra) : rotationAngle(ra)
{
    data.x_pos = x;
    data.y_pos = y;
    
    data.width = 64;
    data.height = 64;
    
    surface = IMG_Load(GET_TEXTURE_PATH("projectiles/arrow_ur"));
    
    velocity.x = cos(ra) * PROJECTILE_SPEED;
    velocity.y = -sin(ra) * PROJECTILE_SPEED;
    
    despawnTimer = 60 * 10;
}

void Projectile::onAddToLevel(Level *level) {}

void Projectile::render(int xoff, int yoff)
{
    if(texture.id == 0) texture = getTexture(surface);
    
    SDL_Rect r = getBoundingBox();
    TRANSFORM_LEVEL_POS(r, xoff, yoff);
    
    SDL_Rect src = {current_anim * 32, 0, 32, 32};

    if(max_anim != 1) renderWithShading(texture, src, r); // Animations cant be rotated...
    else renderWithRotation(texture, src, r, -rotationAngle + PI / 4.0f, true);
    
    level->window->lights.addLight((float) r.x + data.width / 2.0f, (float) r.y + data.height / 2.0f, 5.0f, 0x66FFA080, 0.9, 0.5);
}

void Projectile::update(const uint8_t *keys)
{
    data.x_pos += velocity.x;
    data.y_pos += velocity.y;
    
    SDL_Rect r = getBoundingBox();
    Player *player = level->getLocalPlayer();
    TRANSFORM_LEVEL_POS(r, player->getOffsetX(), player->getOffsetY());
    
    if(++anim_timer >= 7)
    {
        current_anim = (current_anim + 1) % max_anim;
        anim_timer = 0;
    }
    
    if(r.x < 0 || r.x + r.w >= GAME_WIDTH || r.y < 0 || r.y + r.h >= GAME_HEIGHT || --despawnTimer < 0)
    {
        // Despawn...
        level->removeEntity(this); // Stops render & update
    }
    
    float x_pos_front = data.x_pos + data.width * (0.5f + cos(rotationAngle) / 2.0f);
    float y_pos_front = data.y_pos + data.height * (0.5f + sin(rotationAngle) / 2.0f);
    
    float x_pos_end = data.x_pos + data.width * (0.5f - cos(rotationAngle) / 2.0f);
    float y_pos_end = data.y_pos + data.height * (0.5f - sin(rotationAngle) / 2.0f);
    
    float xstep = (x_pos_end - x_pos_front) / PROJECTILE_ACCURACY;
    float ystep = (y_pos_end - y_pos_front) / PROJECTILE_ACCURACY;

    // Find buildings
    for(int i = 0; i <= PROJECTILE_ACCURACY; i++)
    {
        if(level->getBuildingCollision(x_pos_front + i * xstep, y_pos_front + i * ystep))
        {
            velocity = {0, 0}; // Stop right at the wall
        }
    }
    
    // Find enemies in close proximity?
    for(size_t i = 0; i < level->entities.size(); i++)
    {
        auto *enemy = dynamic_cast<Enemy*>(level->entities[i]);
        if(enemy == nullptr || !enemy->isAlive) continue; // Couldnt cast to enemy --> isnt an enemy
        
        if(LENGTH(enemy->data.x_pos - data.x_pos, enemy->data.y_pos - data.y_pos) > LENGTH(data.width, data.height))
        {
            // Out of reach... continue
            continue;
        }
        
        for(int i = 0; i <= PROJECTILE_ACCURACY; i++)
        {
            if(enemy->isInside(x_pos_front + i * xstep, y_pos_front + i * ystep))
            {
                enemy->takeDamage(damage);
                level->removeEntity(this);
            }
        }
    }
}
