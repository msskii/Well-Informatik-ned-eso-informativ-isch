//
//  Level.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Level.hpp"

Level::Level(int w, int h) : tiles(new Tile[w * h]), player(new Player()) // Number of tiles
{
    for(int i = 0; i < w * h; i++)
    {
        tiles[i] = Tile(i % w, i / w);
    }
}

void Level::render(SDL_Renderer *renderer)
{
    player->render(renderer);
}
