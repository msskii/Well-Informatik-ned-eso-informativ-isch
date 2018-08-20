//
//  Player.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Player.hpp"

Player::Player()
{
    
}

void Player::updateMovement(float dx, float dy)
{
    _x += dx;
    _y += dy;    
}

void Player::render(SDL_Renderer *renderer, int x, int y)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
    SDL_Rect rect = {PLAYER_OFFSET_X, PLAYER_OFFSET_Y, PLAYER_WIDTH, PLAYER_HEIGHT};
    SDL_RenderFillRect(renderer, &rect);
}
