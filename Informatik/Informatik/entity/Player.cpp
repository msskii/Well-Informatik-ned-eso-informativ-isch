//
//  Player.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Player.hpp"

Player::Player(Level *l) : level(l)
{
    surface = IMG_Load((TEXTURE_PATH + "player_boy.png").c_str());
}

bool Player::isInside(float dx, float dy)
{
    if(_x + dx < 0 || _x + dx >= TILE_SIZE * level->width || _y + dy < 0 || _y + dy >= TILE_SIZE * level->height) return true; // Out of bounds = you cant walk
    
    if(level->getTile((int)((_x + dx) / TILE_SIZE), (int)((_y + dy) / TILE_SIZE)).data.tileZ != _z) return true;
    if(level->getTile((int)((_x + dx) / TILE_SIZE), (int)((_y + dy + PLAYER_HEIGHT) / TILE_SIZE)).data.tileZ != _z) return true;
    if(level->getTile((int)((_x + dx + PLAYER_WIDTH) / TILE_SIZE), (int)((_y + dy) / TILE_SIZE)).data.tileZ != _z) return true;
    if(level->getTile((int)((_x + dx + PLAYER_WIDTH) / TILE_SIZE), (int)((_y + dy + PLAYER_HEIGHT) / TILE_SIZE)).data.tileZ != _z) return true;
    
    return false;
}

void Player::correctMovement(float &dx, float &dy)
{
    if(isInside(dx, dy))
    {        
        float xmax = 0;
        for(xmax = 0; xmax < STEP_ACCURACY; xmax++) // Walk in 1/n of one step
        {
            if(isInside(dx * xmax / STEP_ACCURACY, dy)) break;
        }
        --xmax; // Not up to and with (inside), just up to the thing
        float ymax = 0;
        for(ymax = 0; ymax < STEP_ACCURACY; ymax++) // Walk in 1/n of one step
        {
            if(isInside(dx * xmax / STEP_ACCURACY, dy * ymax / STEP_ACCURACY)) break;
        }
        --ymax; // Not up to and with (inside), just up to the thing
        for(xmax = 0; xmax < STEP_ACCURACY; xmax++) // Walk in 1/n of one step
        {
            if(isInside(dx * xmax / STEP_ACCURACY, dy * ymax / STEP_ACCURACY)) break;
        }
        --xmax;
        
        
        dx *= xmax / STEP_ACCURACY;
        dy *= ymax / STEP_ACCURACY;
    }
}

void Player::updateMovement(float dx, float dy)
{
    if(!inControl) return;

    correctMovement(dx, dy);
    
    walking = dx != 0 || dy != 0;
    
    if(dx > 0) direction = RIGHT;
    else if(dx < 0) direction = LEFT;
    else if(dy > 0) direction = DOWN;
    else if(dy < 0) direction = UP;
    
    _x += dx;
    _y += dy;
    
    if(_x < 0) _x = 0;
    if(_y < 0) _y = 0;
    if(_x >= (level->width - 1) * TILE_SIZE) _x = (float)((level->width - 1) * TILE_SIZE);
    if(_y >= (level->height - 1) * TILE_SIZE) _y = (float)((level->height - 1) * TILE_SIZE);
}

void Player::render(SDL_Renderer *renderer, int x, int y)
{
    if(walking && timer++ >= 10) // one second
    {
        timer = 0;
        anim = (anim + 1) % 4;
    }
    else if(!walking)
    {
        timer = 0;
        anim = 0;
    }
    
    if(texture == nullptr)
    {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        return;
    }
    
    SDL_Rect src = {32 * anim, 32 * direction, 32, 32};
    SDL_Rect dst = {PLAYER_OFFSET_X, PLAYER_OFFSET_Y, PLAYER_WIDTH, PLAYER_HEIGHT};
    SDL_RenderCopy(renderer, texture, &src, &dst);
}
