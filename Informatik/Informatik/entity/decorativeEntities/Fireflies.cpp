//
//  Fireflies.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 24.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Fireflies.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <math.h>
#include "../../level/Level.hpp"

#define MAX_SPEED 0.6f

Fireflies::Fireflies(float x, float y)
{
    data.x_pos = x;
    data.y_pos = y;
    data.width = 0;
    data.height = 0;
    
    
}

void Fireflies::render(int xoff, int yoff)
{
    SDL_Rect r = getBoundingBox();
    TRANSFORM_LEVEL_POS(r, xoff, yoff);
    for(int i = 0; i < Flycount; i++)
    {
        int fly = i * 4;
        level->window->lights.addLight((float) r.x + flypos[fly], (float) r.y + flypos[fly+1], 0.6f, 0xFF00A0FF, 2.0f, 1.0f);
    }
}

void Fireflies::update(const uint8_t *keys)
{
    for(int i = 0; i<Flycount; i++)
    {
        int fly = i * 4;
        //calculate vector to middle of tile, then add one 1000th of it to the direction vector and a bit random to keep an unclear pattern
        flypos[(fly)+2] += (32 - flypos[fly] + (rand() % 40) - 20) / 5000;
        flypos[(fly)+3] += (32 - flypos[fly+1] + (rand() % 40) - 20) / 5000;
        //limit max speed
        float speed = sqrt(pow(flypos[(fly)+2],2)+pow(flypos[(fly)+3],2));
        if(speed > MAX_SPEED)
        {
            flypos[(fly)+2] *= MAX_SPEED / speed;
            flypos[(fly)+3] *= MAX_SPEED / speed;
        }
        flypos[fly] += flypos[fly+2];
        flypos[fly+1] += flypos[fly+3];
    }
}

void Fireflies::onAddToLevel(Level *level)
{
    srand((uint32_t) time(NULL));
    for(int i = 0; i < Flycount; i++)
    {
        int fly = i * 4;
        //x
        flypos[fly] = (float) (rand() % 32) + 16.0f;
        //y
        flypos[fly+1] = (float) (rand() % 32) + 16.0f;
        //dx
        flypos[fly+2] = (float) (rand() % 100) / 100.0f;
        //dy
        flypos[fly+3] = (float) (rand() % 100) / 100.0f;
    }
}



