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
#include "../../level/Level.hpp"

Fireflies::Fireflies(float x, float y)
{
    data.x_pos = x;
    data.y_pos = y;
    
    
}

void Fireflies::render(int xoff, int yoff)
{
    
    SDL_Rect r = getBoundingBox();
    TRANSFORM_LEVEL_POS(r, xoff, yoff);
    for(int i = 0; i<Flycount; i++)
    {
        level->window->lights.addLight({(float) r.x + flypos[4*i], (float) r.y + flypos[(4*i)+1], 5.0f, 0, 0.2, 0.8, 0.1});
    }
    
}

void Fireflies::update(const uint8_t *keys)
{
    for(int i = 0; i<Flycount; i++)
    {
        //calculate vector to middle of tile, then add one 100th of it to the direction vector
        flypos[(4*i)+2] += (32 - flypos[4*i]) / 1000;
        flypos[(4*i)+3] += (32 - flypos[4*i+1]) / 1000;
        flypos[4*i] += flypos[(4*i)+2];
        flypos[4*i+1] += flypos[4*i+3];
    }
    printf("xpos %f\n", flypos[0]);
    printf("xpos2 %f\n", flypos[4]);
    
}

void Fireflies::onAddToLevel(Level *level)
{
    srand((uint)time(NULL));
    for(int i = 0; i<Flycount; i++)
    {
        //x
        flypos[4*i] = rand() % 64;
        srand((uint)time(NULL));
        //y
        flypos[(4*i)+1] = rand() % 64;
        //dx
        flypos[(4*i)+2] = (rand() % 100) / 10;
        //dy
        flypos[(4*i)+3] = (rand() % 100) / 10;
    }
}



