//
//  Level.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Level.hpp"

Level::Level(int w, int h) : width(w), height(h), tiles(new Tile[w * h]), player(new Player(this)) // Number of tiles
{
    for(int i = 0; i < w * h; i++)
    {
        tiles[i] = Tile(i % w, i / w);
    }
    
    tiles[105].tileZ = 1;
    tiles[106].tileZ = 1;
}

void Level::render(SDL_Renderer *renderer)
{
    int xoffset = -player->_x;
    int yoffset = -player->_y;
    
    for(int i = 0; i < width * height; i++)
    {
        tiles[i].render(renderer, xoffset + PLAYER_OFFSET_X, yoffset + PLAYER_OFFSET_Y);
    }
    player->render(renderer, xoffset, yoffset);
}

Tile Level::getTile(int screenX, int screenY)
{
    return tiles[screenX + width * screenY];
}
