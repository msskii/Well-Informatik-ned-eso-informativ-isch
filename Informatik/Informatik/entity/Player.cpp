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
    if(realPosX + dx < 0 || realPosX + dx >= TILE_SIZE * level->width || realPosY + dy < 0 || realPosY + dy >= TILE_SIZE * level->height) return true; // Out of bounds = you cant walk
    
    if(level->getTile((int)((realPosX + dx) / TILE_SIZE), (int)((realPosY + dy) / TILE_SIZE)).data.tileZ != _z) return true;
    if(level->getTile((int)((realPosX + dx) / TILE_SIZE), (int)((realPosY + dy + PLAYER_HEIGHT) / TILE_SIZE)).data.tileZ != _z) return true;
    if(level->getTile((int)((realPosX + dx + PLAYER_WIDTH) / TILE_SIZE), (int)((realPosY + dy) / TILE_SIZE)).data.tileZ != _z) return true;
    if(level->getTile((int)((realPosX + dx + PLAYER_WIDTH) / TILE_SIZE), (int)((realPosY + dy + PLAYER_HEIGHT) / TILE_SIZE)).data.tileZ != _z) return true;
    
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
    
    realPosX += dx;
    realPosY += dy;
    
    if(realPosX < 0) realPosX = 0;
    if(realPosY < 0) realPosY = 0;
    if(realPosX >= (level->width - 1) * TILE_SIZE) realPosX = (float)((level->width - 1) * TILE_SIZE);
    if(realPosY >= (level->height - 1) * TILE_SIZE) realPosY = (float)((level->height - 1) * TILE_SIZE);
    
    _x = realPosX;
    _y = realPosY;
    
    if(_x <= ((GAME_WIDTH + PLAYER_WIDTH) / 2))
    {
        _x = ((GAME_WIDTH + PLAYER_WIDTH) / 2);
        xoff = ((GAME_WIDTH + PLAYER_WIDTH) / 2) - realPosX;
    }
    else if(_x >= level->width * TILE_SIZE - ((GAME_WIDTH - PLAYER_WIDTH) / 2))
    {
        _x = level->width * TILE_SIZE - ((GAME_WIDTH - PLAYER_WIDTH) / 2);
        xoff = level->width * TILE_SIZE - ((GAME_WIDTH - PLAYER_WIDTH) / 2) - realPosX;
    }
    
    if(_y < ((GAME_HEIGHT + PLAYER_HEIGHT) / 2))
    {
        _y = ((GAME_HEIGHT + PLAYER_HEIGHT) / 2);
        yoff = ((GAME_HEIGHT + PLAYER_HEIGHT) / 2) - realPosY;
    }
    else if(_y >= level->height * TILE_SIZE - ((GAME_HEIGHT - PLAYER_HEIGHT) / 2))
    {
        _y = level->height * TILE_SIZE - ((GAME_HEIGHT - PLAYER_HEIGHT) / 2);
        yoff = level->height * TILE_SIZE - ((GAME_HEIGHT - PLAYER_HEIGHT) / 2) - realPosY;
    }
}

void Player::render(SDL_Renderer *renderer, int x, int y)
{
    //animation speed scales with player speed
    if(walking && (timer++ * SPEED) >= 50)
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
    SDL_Rect dst = {PLAYER_OFFSET_X - xoff, PLAYER_OFFSET_Y - yoff, PLAYER_WIDTH, PLAYER_HEIGHT};
    SDL_RenderCopy(renderer, texture, &src, &dst);
}
