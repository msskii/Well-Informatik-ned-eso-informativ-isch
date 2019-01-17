//
//  PlayerOverlay.cpp
//  Informatik
//
//  Created by Aaron Hodel on 11.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "PlayerOverlay.hpp"
#include "Shop.hpp"
#include "../../projectile/Spell.hpp"

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
    if(window) player = window->level->getLocalPlayer();
    int color = 0xFF000000;
    if(player->data.y_pos > 100)
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
    
    for(int i = 0; i < MAX_SPELLS; i++) // Render the "spells"
    {
        SDL_Rect dst = {GAME_WIDTH - 100 * (MAX_SPELLS - i), GAME_HEIGHT - 100, 100, 100};
        
        if(player->spells[i])
        {
            fillRect(0xFFFF00FF, dst); // TODO: render some graphic that represents that spell
            if(player->spells[i]->cooldownTimer > 0)
            {
                float percentage = player->spells[i]->cooldownTimer / player->spells[i]->cooldown;
                dst.h = (int)(100.0f * percentage);
                dst.y = GAME_HEIGHT - (int)(100.0f * percentage);
                fillRect(0x7FFFFFFF, dst);
            }
        }
        else
        {
            fillRect(0xFF000000, dst);
        }
    }
    
    bool healthChange = lastHealth != player->animationHealth;
    
    lastHealth = player->currentHealth;
    drawTextAspect((std::to_string((int) lastHealth) + "/" + std::to_string((int) player->maxHealth)).c_str(), color, {1150, 20, 750, 60}, cachedHealth, transition || healthChange);
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
