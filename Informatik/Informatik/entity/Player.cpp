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
    player_surface = IMG_Load(GET_FILE_PATH(TEXTURE_PATH, "/player_boy.png"));
}

// Helper function for intersections with other things (xpos & ypos are the players position while the rest are the parameters of the thing trying to compare to)
bool intersectWith(int xpos1, int ypos1, int x, int y, int w, int h)
{
    if((xpos1) >= x && (xpos1) <= x + w && (ypos1) >= y && (ypos1) <= y + h) return true;
    if((xpos1 + PLAYER_WIDTH) > x && (xpos1 + PLAYER_WIDTH) < x + w && (ypos1) > y && (ypos1) <= y + h) return true;
    if((xpos1) >= x && (xpos1) <= x + w && (ypos1 + PLAYER_HEIGHT) > y && (ypos1 + PLAYER_HEIGHT) < y + h) return true;
    if((xpos1 + PLAYER_WIDTH) > x && (xpos1 + PLAYER_WIDTH) < x + w && (ypos1 + PLAYER_HEIGHT) > y && (ypos1 + PLAYER_HEIGHT) < y + h) return true;
    return false;
}

#define MARGIN 4

bool Player::isInside(float dx, float dy)
{
    if(x_pos + dx < 0 || x_pos + dx >= TILE_SIZE * level->width || y_pos + dy < 0 || y_pos + dy >= TILE_SIZE * level->height) return true; // Out of bounds = you cant walk
    
    if(level->getTile((int)((x_pos + dx + MARGIN) / TILE_SIZE), (int)((y_pos + dy + MARGIN) / TILE_SIZE)).data.tileZ != _z) return true;
    if(level->getTile((int)((x_pos + dx + MARGIN) / TILE_SIZE), (int)((y_pos + dy + PLAYER_HEIGHT - MARGIN) / TILE_SIZE)).data.tileZ != _z) return true;
    if(level->getTile((int)((x_pos + dx + PLAYER_WIDTH - MARGIN) / TILE_SIZE), (int)((y_pos + dy + MARGIN) / TILE_SIZE)).data.tileZ != _z) return true;
    if(level->getTile((int)((x_pos + dx + PLAYER_WIDTH - MARGIN) / TILE_SIZE), (int)((y_pos + dy + PLAYER_HEIGHT - MARGIN) / TILE_SIZE)).data.tileZ != _z) return true;
    
    for(int i = 0; i < level->entities.size(); i++)
    {
        if(intersectWith(x_pos + dx, y_pos + dy, level->entities[i]->data.x_pos, level->entities[i]->data.y_pos, level->entities[i]->data.width, level->entities[i]->data.height)) return true;
    }
    
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

    // Walking into stuff
    if(dx > 0) direction = RIGHT;
    else if(dx < 0) direction = LEFT;
    else if(dy > 0) direction = DOWN;
    else if(dy < 0) direction = UP;
    
    walking = dx != 0 || dy != 0;
    
    correctMovement(dx, dy);
    
    if(dx > 0) direction = RIGHT;
    else if(dx < 0) direction = LEFT;
    else if(dy > 0) direction = DOWN;
    else if(dy < 0) direction = UP;
    
    x_pos += dx;
    y_pos += dy;
    
    if(x_pos < 0) x_pos = 0;
    if(y_pos < 0) y_pos = 0;
    if(x_pos >= (level->width - 1) * TILE_SIZE) x_pos = (float)((level->width - 1) * TILE_SIZE);
    if(y_pos >= (level->height - 1) * TILE_SIZE) y_pos = (float)((level->height - 1) * TILE_SIZE);
    
    _x = x_pos;
    _y = y_pos;
    
    if(_x <= ((GAME_WIDTH + PLAYER_WIDTH) / 2))
    {
        _x = ((GAME_WIDTH + PLAYER_WIDTH) / 2);
        xoff = ((GAME_WIDTH + PLAYER_WIDTH) / 2) - x_pos;
    }
    else if(_x >= level->width * TILE_SIZE - ((GAME_WIDTH - PLAYER_WIDTH) / 2))
    {
        _x = level->width * TILE_SIZE - ((GAME_WIDTH - PLAYER_WIDTH) / 2);
        xoff = level->width * TILE_SIZE - ((GAME_WIDTH - PLAYER_WIDTH) / 2) - x_pos;
    }
    
    if(_y < ((GAME_HEIGHT + PLAYER_HEIGHT) / 2))
    {
        _y = ((GAME_HEIGHT + PLAYER_HEIGHT) / 2);
        yoff = ((GAME_HEIGHT + PLAYER_HEIGHT) / 2) - y_pos;
    }
    else if(_y >= level->height * TILE_SIZE - ((GAME_HEIGHT - PLAYER_HEIGHT) / 2))
    {
        _y = level->height * TILE_SIZE - ((GAME_HEIGHT - PLAYER_HEIGHT) / 2);
        yoff = level->height * TILE_SIZE - ((GAME_HEIGHT - PLAYER_HEIGHT) / 2) - y_pos;
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
        texture = SDL_CreateTextureFromSurface(renderer, player_surface);
        return;
    }
    
    SDL_Rect src = {32 * anim, 32 * direction, 32, 32};
    SDL_Rect dst = {PLAYER_OFFSET_X - xoff, PLAYER_OFFSET_Y - yoff, PLAYER_WIDTH, PLAYER_HEIGHT};
    SDL_RenderCopy(renderer, texture, &src, &dst);
}
