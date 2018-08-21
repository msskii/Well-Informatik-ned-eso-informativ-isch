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
    
}

bool Player::isInside(float dx, float dy)
{
    if(level->getTile(((_x + dx) / TILE_SIZE), ((_y + dy) / TILE_SIZE)).tileZ != _z) return true;
    if(level->getTile(((_x + dx) / TILE_SIZE), ((_y + dy + PLAYER_HEIGHT) / TILE_SIZE)).tileZ != _z) return true;
    if(level->getTile(((_x + dx + PLAYER_WIDTH) / TILE_SIZE), ((_y + dy) / TILE_SIZE)).tileZ != _z) return true;
    if(level->getTile(((_x + dx + PLAYER_WIDTH) / TILE_SIZE), ((_y + dy + PLAYER_HEIGHT) / TILE_SIZE)).tileZ != _z) return true;
    
    return false;
}

#define STEP_ACCURACY 100.0
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
    lx = dx > 0 ? 1 : dx == 0 ? 0 : -1;
    ly = dy > 0 ? 1 : dy == 0 ? 0 : -1;
    correctMovement(dx, dy);
    
    _x += dx;
    _y += dy;
    
    if(_x < 0) _x = 0;
    if(_y < 0) _y = 0;
    if(_x >= (level->width - 1) * TILE_SIZE) _x = (level->width - 1) * TILE_SIZE;
    if(_y >= (level->height - 1) * TILE_SIZE) _y = (level->height - 1) * TILE_SIZE;
}

void Player::render(SDL_Renderer *renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_Rect rect = {PLAYER_OFFSET_X, PLAYER_OFFSET_Y, PLAYER_WIDTH, PLAYER_HEIGHT};
    SDL_RenderFillRect(renderer, &rect);
}
