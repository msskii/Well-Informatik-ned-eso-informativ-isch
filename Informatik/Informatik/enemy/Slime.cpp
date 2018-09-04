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
}

bool Slime::isInside(float x, float y)
{
    return false;
}
void Slime::onAddToLevel(Level *level) {}

void Slime::render(SDL_Renderer *renderer, int xoff, int yoff)
{
    SDL_Rect r = { (int) data.x_pos, (int) data.y_pos, (int) data.width, (int) data.height};
    COLOR(renderer, 0xFFFF00FF);
    SDL_RenderFillRect(renderer, &r);
}

void Slime::update(const uint8_t *keys) {}
