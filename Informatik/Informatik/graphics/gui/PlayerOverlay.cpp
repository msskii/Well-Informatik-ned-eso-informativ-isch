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
    shouldLevelBeUpdated = true; // Dont pause the game because of this overlay...
    
    backsurface = IMG_Load(GET_TEXTURE_PATH("backgrounds/PlayerOverlay_new"));
    backsurface_under = IMG_Load(GET_TEXTURE_PATH("backgrounds/PlayerOverlay_under"));
    hpbarsurface = IMG_Load(GET_TEXTURE_PATH("backgrounds/hp_bar_player"));
    manabarsurface = IMG_Load(GET_TEXTURE_PATH("backgrounds/hp_bar_player"));
    
    spelliconsurface = IMG_Load(GET_TEXTURE_PATH("elements/spellicons"));
    spellbordersurface = IMG_Load(GET_TEXTURE_PATH("elements/spellBorders"));
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
    backtexture_under = getTexture(backsurface_under);
    hpbartexture = getTexture(hpbarsurface);
    manabartexture = getTexture(manabarsurface);
    hpbartransparenttexture = getTexture(hpbartransparentsurface);
    spellicontexture = getTexture(spelliconsurface);
    spellbordertexture = getTexture(spellbordersurface);
}

bool PlayerOverlay::shouldWindowClose() { return false; }

void PlayerOverlay::renderMenu()
{
    if(window) player = window->level->getLocalPlayer();
    int color = 0xFFFFFFFF;
    //render bars
    if(player->data.y_pos > int((24.0/180.0) * GAME_HEIGHT))
    {
        //SDL_RenderCopy(renderer, backtexture, NULL, &window->render_surface->clip_rect);
        renderWithoutShading(backtexture_under, {}, {0,0,GAME_WIDTH,GAME_HEIGHT});
        SDL_Rect dst = {int((210.0/320.0) * GAME_WIDTH), int((6.0/180.0) * GAME_HEIGHT), (int)(104.0 / 320.0 * GAME_WIDTH * player->animationHealth / player->maxHealth), int((12.0/180.0) * GAME_HEIGHT)};
        renderWithoutShading(hpbartexture, {}, dst);
        dst = {int((6.0/320.0) * GAME_WIDTH), int((6.0/180.0) * GAME_HEIGHT), (int)(104.0 / 320.0 * GAME_WIDTH * player->animationMana / player->maxMana), int((12.0/180.0) * GAME_HEIGHT)};
        renderWithoutShading(manabartexture, {}, dst);
        lastState = 0;
        renderWithoutShading(backtexture, {}, {0, 0, GAME_WIDTH, GAME_HEIGHT});
        
        
        
    }
    else
    {
        renderWithoutShading(backtexture_under, {}, {0,0,GAME_WIDTH,GAME_HEIGHT}, 0.2f);
        SDL_Rect dst = {int((210.0/320.0) * GAME_WIDTH), int((6.0/180.0) * GAME_HEIGHT), (int)(104.0 / 320.0 * GAME_WIDTH * player->animationHealth / player->maxHealth), int((12.0/180.0) * GAME_HEIGHT)};
        renderWithoutShading(hpbartransparenttexture, {}, dst, 0.2f);
        dst = {int((6.0/320.0) * GAME_WIDTH), int((6.0/180.0) * GAME_HEIGHT), (int)(104.0 / 320.0 * GAME_WIDTH * player->animationMana / player->maxMana), int((12.0/180.0) * GAME_HEIGHT)};
        renderWithoutShading(manabartexture, {}, dst, 0.2f);
        renderWithoutShading(backtexture, {}, {0, 0, GAME_WIDTH, GAME_HEIGHT}, 0.2f);
        color = 0x7FFFFFFF; // Slightly transparent
        
        lastState = 1;
    }
    //the nubers indicating mana
    drawTextAspect((std::to_string((int) player->lastHealth) + "/" + std::to_string((int) player->maxHealth)).c_str(), color, {int((212.0/320.0) * GAME_WIDTH), int((8.0/180.0) * GAME_HEIGHT), 200, int((8.0/180.0) * GAME_HEIGHT)});
    drawTextAspect((std::to_string((int) player->lastMana) + "/" + std::to_string((int) player->maxMana)).c_str(), color, {int((8.0/320.0) * GAME_WIDTH), int((8.0/180.0) * GAME_HEIGHT), 200, int((8.0/180.0) * GAME_HEIGHT)});
    
    
    for(int i = 0; i < (int) player->spells.size(); i++) // Render the "spells"
    {
        SDL_Rect dst = {int((145.0/320.0) * GAME_WIDTH) + (i - 2) * int(18.0 / 320.0 * GAME_WIDTH) , int((156.0/180.0) * GAME_HEIGHT), int((16.0/180.0) * GAME_HEIGHT), int((16.0/180.0) * GAME_HEIGHT)};
        if(i < 2){
            dst.x = int((105.0/320.0) * GAME_WIDTH) + i * int(18.0 / 320.0 * GAME_WIDTH);
        }
        if(player->spells[i])
        {
            renderWithoutShading(spellicontexture, {64 * player->spells[i]->spellID, 0, 64, 64}, dst); // Maybe all icons in the same texture and then instead of {} the area where the one of the spellID is? like {SPELL_ICON_WIDTH * spellID, 0, SPELL_ICON_WIDTH, SPELL_ICON_HEIGHT}
            renderWithoutShading(spellbordertexture, {0, 0, 64, 64}, dst);
            if(player->spells[i]->cooldownTimer > 0)
            {
                float percentage = player->spells[i]->cooldownTimer / player->spells[i]->cooldown;
                dst.h = (int)(16.0/180.0 * GAME_HEIGHT * percentage);
                dst.y = GAME_HEIGHT - dst.h - int(8.0 / 320.0 * GAME_WIDTH);
                fillRect(0x9F0000FF, dst);
            }
        }
        else
        {
            fillRect(0xFF000000, dst);
        }
    }
    
    //render cave gui
    if (window->currentLevel == 0) drawTextCentered((std::to_string((int)window->cave->floor)).c_str(), color, {0, int((8.0/320.0) * GAME_WIDTH), GAME_WIDTH, int((8.0/320.0) * GAME_WIDTH)});
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
