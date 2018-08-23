//
//  SDL_Util.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "SDL_Util.hpp"

TTF_Font *font = nullptr;
float SCALE_X = 0, SCALE_Y = 0;

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
        SDL_Rect dst = {x * srfc->w / w, y * srfc->h / h, srfc->w, srfc->h}; // Desination rect
        
        SDL_RenderSetScale(renderer, SCALE_X * (float) w / (float) srfc->w, SCALE_Y * (float) h / (float) srfc->h); // Set scaling
        
        SDL_RenderCopy(renderer, texture, NULL, &dst); // Render stuff
        
        SDL_RenderSetScale(renderer, SCALE_X, SCALE_Y); // Reset scale
        
        // Clean up
        SDL_FreeSurface(srfc);
        SDL_DestroyTexture(texture);
    }
}
