//
//  PlayerOverlay.cpp
//  Informatik
//
//  Created by Aaron Hodel on 11.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "PlayerOverlay.hpp"

PlayerOverlay::PlayerOverlay(Player *p) : player(p)
{
    background_surface = IMG_Load(GET_TEXTURE_PATH("backgrounds/PlayerOverlay_under"));
    shouldLevelBeUpdated = true; // Dont pause the game because of this overlay...
    
    backsurface = IMG_Load(GET_TEXTURE_PATH("backgrounds/PlayerOverlay"));
    hpbarsurface = IMG_Load(GET_TEXTURE_PATH("backgrounds/hp_bar_player"));
    hpbartransparentsurface = IMG_Load(GET_TEXTURE_PATH("backgrounds/hp_bar_player_transparent"));
}

bool PlayerOverlay::shouldWindowClose() { return false; }

void PlayerOverlay::renderMenu(SDL_Renderer *renderer)
{
    if(backtexture == nullptr) backtexture = SDL_CreateTextureFromSurface(renderer, backsurface);
    if(hpbartexture == nullptr) hpbartexture = SDL_CreateTextureFromSurface(renderer, hpbarsurface);
    if(hpbartransparenttexture == nullptr) hpbartransparenttexture = SDL_CreateTextureFromSurface(renderer, hpbartransparentsurface);
    
    int color = 0xFF000000;
    if(player->y_pos > 100)
    {
        SDL_RenderCopy(renderer, backtexture, NULL, &window->render_surface->clip_rect);
        
        SDL_Rect dst = {1150, 10, (int)(750 * player->animationHealth / player->maxHealth), 80};
        SDL_RenderCopy(renderer, hpbartexture, NULL, &dst);
        
        if(lastState == 1) transition = true;
        lastState = 0;
    }
    else
    {
        SDL_Rect dst = {1150, 10, (int)(750 * player->currentHealth / player->maxHealth), 80};
        SDL_RenderCopy(renderer, hpbartransparenttexture, NULL, &dst);
        
        color = 0x7F000000;
        
        if(lastState == 0) transition = true;
        lastState = 1;
    }
    
    if(cachedHealth.texture == nullptr || player->currentHealth != lastHealth || transition)
    {
        lastHealth = player->currentHealth;
        drawTextAspect(renderer, (std::to_string((int) lastHealth) + "/" + std::to_string((int) player->maxHealth)).c_str(), color, 1150, 20, 750, 60, cachedHealth);
        transition = false;
    }
    else
    {
        SDL_Rect dst = {1150, 20, cachedHealth.textwidth, cachedHealth.textheight};
        SDL_RenderCopy(renderer, cachedHealth.texture, NULL, &dst);
    }
}

void PlayerOverlay::drawOverlay(SDL_Renderer *renderer) {}
void PlayerOverlay::updateMenu(const uint8_t *keys) {}
void PlayerOverlay::onOpen(){}
void PlayerOverlay::onClose() {}
