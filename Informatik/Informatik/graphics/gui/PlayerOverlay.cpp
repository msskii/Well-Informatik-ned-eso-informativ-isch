//
//  PlayerOverlay.cpp
//  Informatik
//
//  Created by Aaron Hodel on 11.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "PlayerOverlay.hpp"
#include "Shop.hpp"

PlayerOverlay::PlayerOverlay(Player *p) : player(p)
{
    background_surface = IMG_Load(GET_TEXTURE_PATH("backgrounds/PlayerOverlay_under"));
    background_texture = getTexture(background_surface);
    shouldLevelBeUpdated = true; // Dont pause the game because of this overlay...
    
    backsurface = IMG_Load(GET_TEXTURE_PATH("backgrounds/PlayerOverlay"));
    hpbarsurface = IMG_Load(GET_TEXTURE_PATH("backgrounds/hp_bar_player"));
    manabarsurface = IMG_Load(GET_TEXTURE_PATH("backgrounds/hp_bar_player"));
    //change the hp bar from green to blue
    SDL_PixelFormat *fmt = manabarsurface->format;
    uint32_t *pixels = (uint32_t*) manabarsurface->pixels;
    for(int i = 0; i < manabarsurface->w * manabarsurface->h; i++)
    {
        Uint32 temp;
        temp = (pixels[i] & fmt->Amask) | (((pixels[i] & fmt->Gmask) >> fmt->Gshift) << fmt->Bshift);
        pixels[i] = temp;
    }
    
    hpbartransparentsurface = IMG_Load(GET_TEXTURE_PATH("backgrounds/hp_bar_player_transparent"));
    
    backtexture = getTexture(backsurface);
    hpbartexture = getTexture(hpbarsurface);
    manabartexture = getTexture(manabarsurface);
    hpbartransparenttexture = getTexture(hpbartransparentsurface);
}

bool PlayerOverlay::shouldWindowClose() { return false; }

void PlayerOverlay::renderMenu()
{
    if(window) player = window->level->getLocalPlayer();
    int color = 0xFF000000;
    if(player->data.y_pos > 100)
    {
        //SDL_RenderCopy(renderer, backtexture, NULL, &window->render_surface->clip_rect);
        renderWithoutShading(backtexture, {}, {0, 0, GAME_WIDTH, GAME_HEIGHT});
        
        SDL_Rect dst = {1150, 10, (int)(750 * player->animationHealth / player->maxHealth), 80};
        renderWithoutShading(hpbartexture, {}, dst);
        dst = {10, 10, (int)(750 * player->animationMana / player->maxMana), 80};
        renderWithoutShading(manabartexture, {}, dst);
        if(lastState == 1) transition = true;
        lastState = 0;
    }
    else
    {
        SDL_Rect dst = {1150, 10, (int)(750 * player->currentHealth / player->maxHealth), 80};
        renderWithoutShading(hpbartransparenttexture, {}, dst);
        dst = {10, 10, (int)(750 * player->animationMana / player->maxMana), 80};
        renderWithoutShading(manabartexture, {}, dst);
        color = 0x7F000000;
        
        if(lastState == 0) transition = true;
        lastState = 1;
    }
    
    bool healthChange = lastHealth != player->animationHealth;
    bool manaChange = lastMana != player->animationMana;
    
    lastHealth = player->currentHealth;
    lastMana = player->currentMana;
    drawTextAspect((std::to_string((int) lastHealth) + "/" + std::to_string((int) player->maxHealth)).c_str(), color, {1150, 20, 750, 60}, cachedHealth, transition || healthChange);
    drawTextAspect((std::to_string((int) lastMana) + "/" + std::to_string((int) player->maxMana)).c_str(), color, {20, 20, 750, 60}, cachedMana, transition || manaChange);
    transition = false;
}

void PlayerOverlay::updateMenu(const uint8_t *keys)
{
    bool kpressed = keys[SDL_SCANCODE_K];
    bool jpressed = keys[SDL_SCANCODE_J];
    
    if(kpressed && !kp) // Just to test it
    {
        window->openMenu(new Shop("ShopOverlay", 1000, { {new Item("test"), 1, 10, 9}, {new Item("test2"), 2, 100, 90}, {new Item("infinity"), 1, 1000, 800} }));
    }
    else if(jpressed && !jp) // Just to test it
    {
        window->openMenu(new Shop("ShopOverlay", 1000, player));
    }
    
    kp = kpressed;
    jp = jpressed;
}

void PlayerOverlay::onOpen(){}
void PlayerOverlay::onClose() {}
