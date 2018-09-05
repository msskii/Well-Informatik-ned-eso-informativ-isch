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
    
    data.width *= 3;
    enemy_surface = IMG_Load(GET_TEXTURE_PATH("Enemy_BlueSlime"));
}

bool Slime::isInside(float x, float y)
{
    return x >= data.x_pos && y >= data.y_pos && x <= data.x_pos + data.width && y <= data.y_pos + data.height;
}

void Slime::onAddToLevel(Level *level) {}

void Slime::render(SDL_Renderer *renderer, int xoff, int yoff)
{
    if(ATTACKING &&(timer++) >= 5)
    {
        timer = 0;
        anim = (anim + 1) % 10;
    }
    
    {
        texture = SDL_CreateTextureFromSurface(renderer, enemy_surface);
        return;
    }
    
    SDL_Rect src = {32 * anim, 0, 32, 32};
    SDL_Rect dst = getBoundingBox();
    TRANSFORM_LEVEL_POS(dst, xoff, yoff); // Transform r to the level position
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void Slime::update(const uint8_t *keys) {}
