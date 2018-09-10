//
//  Element.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Element.hpp"

std::map<int, SDL_Texture*> textures;

void Element::addToMenu(Menu *menu)
{
    this->menu = menu;
}

void reloadElementTextures(SDL_Renderer *renderer)
{
    printf("[INFO] Reloading Element textures...\n");
    for(int i = 0; i < NUM_TEXTURES; i++)
    {
        SDL_Surface *surface = IMG_Load(GET_TEXTURE_PATH(texturePaths[i]));
        textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
}
