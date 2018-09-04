//
//  Projectile.cpp
//  Informatik
//
//  Created by Aaron Hodel on 04.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Projectile.hpp"

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
}
