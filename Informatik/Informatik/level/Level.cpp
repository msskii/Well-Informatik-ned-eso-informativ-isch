//
//  Level.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Level.hpp"

Level::Level(int w, int h) : width(w), height(h), tiles(new Tile[w * h]), player(new Player()) // Number of tiles
{
    for(int i = 0; i < w * h; i++)
    {
        tiles[i] = Tile(i % w, i / w);
    }
}

void Level::render(SDL_Renderer *renderer)
{
    if(player->_x < 0) player->_x = 0;
    if(player->_y < 0) player->_y = 0;
    if(player->_x >= (width - 1) * TILE_SIZE) player->_x = (width - 1) * TILE_SIZE;
    if(player->_y >= (height - 1) * TILE_SIZE) player->_y = (height - 1) * TILE_SIZE;


    int xoffset = -player->_x;
    int yoffset = -player->_y;
    
    
    for(int i = 0; i < width * height; i++)
    {
        tiles[i].render(renderer, xoffset + PLAYER_OFFSET_X, yoffset + PLAYER_OFFSET_Y);
    }
    player->render(renderer, xoffset, yoffset);
}
