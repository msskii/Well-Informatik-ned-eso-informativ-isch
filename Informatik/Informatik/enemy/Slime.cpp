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
    enemy_surface = IMG_Load(GET_TEXTURE_PATH("Enemy_BlueSlime"));
}

bool Slime::isInside(float x, float y)
{
    return false;
}
void Slime::onAddToLevel(Level *level) {}

void Slime::render(SDL_Renderer *renderer, int xoff, int yoff)
{
    if(ATTACKING &&(timer++) >= 5)
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
    SDL_Rect dst = { (int) data.x_pos, (int) data.y_pos, (int) data.width, (int) data.height};
    TRANSFORM_LEVEL_POS(dst, xoff, yoff); // Transform r to the level position
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void Slime::update(const uint8_t *keys) {}
