//
//  Level.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Level.hpp"
#include "loader/EventActions.hpp"

Level::Level(int w, int h) : width(w), height(h), tiles(new Tile[w * h]), player(new Player(this)) // Number of tiles
{
    for(int i = 0; i < w * h; i++)
    {
        tiles[i] = Tile(i % w, i / w);
    }
    
    tiles[105].tileZ = 1;
    tiles[106].tileZ = 1;
    
    events.push_back(Event(STEP_ON, MOVE_PLAYER, 6, 1, new uint8_t[2] { RIGHT, 2 })); // Move player 2 down
}

void Level::render(SDL_Renderer *renderer)
{
    int xoffset = -player->_x;
    int yoffset = -player->_y;
    
    for(int i = 0; i < width * height; i++)
    {
        tiles[i].render(renderer, xoffset + PLAYER_OFFSET_X, yoffset + PLAYER_OFFSET_Y);
    }
    
    for(int i = 0; i < events.size(); i++)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_Rect r = {events[i].x * TILE_SIZE + xoffset + PLAYER_OFFSET_X, events[i].y * TILE_SIZE + yoffset + PLAYER_OFFSET_Y, TILE_SIZE / 2, TILE_SIZE / 2};
        SDL_RenderFillRect(renderer, &r);
    }
    
    player->render(renderer, xoffset, yoffset);
}

Tile Level::getTile(int screenX, int screenY)
{
    return tiles[screenX + width * screenY];
}
