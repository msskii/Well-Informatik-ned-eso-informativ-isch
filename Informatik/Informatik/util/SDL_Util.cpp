//
//  SDL_Util.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "SDL_Util.hpp"

TTF_Font *font = nullptr;

void drawText(SDL_Renderer *renderer, const char *text, int color, int x, int y)
{    
    if(font == nullptr)
    {
        INFO("Font not yet initialized");
        return;
    }
        
    SDL_Surface *srfc = TTF_RenderText_Solid(font, text, TO_COLOR(color)); // rgba
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, srfc);
    if(text)
    {
        SDL_Rect dst = {x, y, srfc->w, srfc->h};
        SDL_RenderCopy(renderer, texture, NULL, &dst);
        SDL_FreeSurface(srfc);
        SDL_DestroyTexture(texture);
    }
}

void drawText(SDL_Renderer *renderer, const char *text, int color, int x, int y, int w, int h) // With max width & height
{
    if(font == nullptr)
    {
        INFO("Font not yet initialized");
        return;
    }
    
    SDL_Surface *srfc = TTF_RenderText_Solid(font, text, TO_COLOR(color)); // rgba
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, srfc);
    if(text)
    {
        SDL_Rect dst = {x, y, srfc->w, srfc->h};
        SDL_RenderSetScale(renderer, (float) w / (float) srfc->w, (float) h / (float) srfc->h);
        SDL_RenderCopy(renderer, texture, NULL, &dst);
        SDL_RenderSetScale(renderer, 1, 1);
        SDL_FreeSurface(srfc);
        SDL_DestroyTexture(texture);
    }
}
