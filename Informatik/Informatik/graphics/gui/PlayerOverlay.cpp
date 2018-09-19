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
    background_texture = getTexture(background_surface);
    shouldLevelBeUpdated = true; // Dont pause the game because of this overlay...
    
    backsurface = IMG_Load(GET_TEXTURE_PATH("backgrounds/PlayerOverlay"));
    hpbarsurface = IMG_Load(GET_TEXTURE_PATH("backgrounds/hp_bar_player"));
    hpbartransparentsurface = IMG_Load(GET_TEXTURE_PATH("backgrounds/hp_bar_player_transparent"));
    
    backtexture = getTexture(backsurface);
    hpbartexture = getTexture(hpbarsurface);
    hpbartransparenttexture = getTexture(hpbartransparentsurface);
}

bool PlayerOverlay::shouldWindowClose() { return false; }

void PlayerOverlay::renderMenu()
{
    int color = 0xFF000000;
    if(player->y_pos > 100)
    {
        //SDL_RenderCopy(renderer, backtexture, NULL, &window->render_surface->clip_rect);
        renderWithoutShading(backtexture, {}, {0, 0, GAME_WIDTH, GAME_HEIGHT});
        
        SDL_Rect dst = {1150, 10, (int)(750 * player->animationHealth / player->maxHealth), 80};
        renderWithoutShading(hpbartexture, {}, dst);
        if(lastState == 1) transition = true;
        lastState = 0;
    }
    else
    {
        SDL_Rect dst = {1150, 10, (int)(750 * player->currentHealth / player->maxHealth), 80};
        renderWithoutShading(hpbartransparenttexture, {}, dst);
        color = 0x7F000000;
        
        if(lastState == 0) transition = true;
        lastState = 1;
    }
    
    bool healthChange = lastHealth != player->animationHealth;
    
    lastHealth = player->currentHealth;
    drawTextAspect((std::to_string((int) lastHealth) + "/" + std::to_string((int) player->maxHealth)).c_str(), color, {1150, 20, 750, 60}, cachedHealth, transition || healthChange);
    transition = false;
}

void PlayerOverlay::drawOverlay() {}
void PlayerOverlay::updateMenu(const uint8_t *keys) {}
void PlayerOverlay::onOpen(){}
void PlayerOverlay::onClose() {}
