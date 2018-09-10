//
//  Item.cpp
//  Informatik
//
//  Created by Aaron Hodel on 05.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Item.hpp"

Item::Item(const char *itemname, SDL_Renderer *renderer) : name(itemname)
{
    surface = IMG_Load(GET_TEXTURE_PATH("items/" + itemname));
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    
    if(texture == nullptr)
    {
        printf("[WARNING] Couldn't create item texture %s\n", itemname);
        printf("[WARNING] SDL Error: %s\n", SDL_GetError());
    }
}
