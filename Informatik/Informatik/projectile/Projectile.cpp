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
    
    surface = IMG_Load(GET_TEXTURE_PATH("projectiles/arrow_ur"));
    velocity.x = cos(ra) * PROJECTILE_SPEED;
    velocity.y = -sin(ra) * PROJECTILE_SPEED;
}

void Projectile::onAddToLevel(Level *level) {}

void Projectile::render(SDL_Renderer *renderer, int xoff, int yoff)
{
    if(texture == nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
    }
    
    SDL_Rect r = getBoundingBox();
    TRANSFORM_LEVEL_POS(r, xoff, yoff);
    SDL_Point center = {(int) data.width / 2, (int) data.height / 2};
    
    SDL_RenderCopyEx(renderer, texture, NULL, &r, -TO_DEG(rotationAngle) + 45, &center, SDL_FLIP_NONE);
}

void Projectile::update(const uint8_t *keys)
{
    data.x_pos += velocity.x;
    data.y_pos += velocity.y;
    
    SDL_Rect r = getBoundingBox();
    TRANSFORM_LEVEL_POS(r, level->player->getOffsetX(), level->player->getOffsetY());
    
    if(r.x < 0 || r.x + r.w >= GAME_WIDTH || r.y < 0 || r.y + r.h >= GAME_HEIGHT || --despawnTimer < 0)
    {
        // Despawn...
        level->removeEntity(this); // Stops render & update
    }
    
    float x_pos_front = data.x_pos + data.width * (0.5 + cos(rotationAngle) / 2.0);
    float y_pos_front = data.y_pos + data.height * (0.5 + sin(rotationAngle) / 2.0);
    
    // Find enemies in close proximity?
    for(size_t i = 0; i < level->entities.size(); i++)
    {
        auto *enemy = dynamic_cast<Enemy*>(level->entities[i]);
        if(enemy == nullptr || !enemy->isAlive) continue; // Couldnt cast to enemy --> isnt an enemy
        if(enemy->isInside(x_pos_front, y_pos_front))
        {
            enemy->takeDamage(damage);
            level->removeEntity(this);
        }
    }
}
