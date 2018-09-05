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
    data.height *= 3;
    
    slimeColor = (rand() & 0xFF) | (rand() & 0xFF) << 8 | (rand() & 0xFF) << 16;
}

bool Slime::isInside(float x, float y)
{
    return x >= data.x_pos && y >= data.y_pos && x <= data.x_pos + data.width && y <= data.y_pos + data.height;
}

void Slime::onAddToLevel(Level *level) {}

void Slime::render(SDL_Renderer *renderer, int xoff, int yoff)
{
    SDL_Rect r = { (int) data.x_pos, (int) data.y_pos, (int) data.width, (int) data.height};
    TRANSFORM_LEVEL_POS(r, xoff, yoff); // Transform r to the level position
    COLOR(renderer, 0xFF000000 | slimeColor);
    SDL_RenderFillRect(renderer, &r);
    
    renderHP(renderer, xoff, yoff);
}

void Slime::update(const uint8_t *keys) {}
