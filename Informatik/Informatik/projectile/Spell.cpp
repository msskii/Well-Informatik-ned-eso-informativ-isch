//
//  Spell.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 13.11.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Spell.hpp"

Spell::Spell(SpellType spellID, float damageModifier, Level *level) : spellID(spellID), level(level)
{
    switch (spellID)
    {
        case SPELL_DASH:
            //set cooldowns and damage
            damage = 0.5 * damageModifier;
            cooldown = 0.2;
            manaCost = 5;
            spellTicks = 5;
            renderOverPlayer = false;
            spellsurface = IMG_Load(GET_TEXTURE_PATH("player/Character_Animation"));
            {
                SDL_PixelFormat *fmt = spellsurface->format;
                uint32_t *pixels = (uint32_t*) spellsurface->pixels;
                for(int i = 0; i < spellsurface->w * spellsurface->h; i++)
                {
                    if ((pixels[i] & fmt->Amask) != 0) {
                        pixels[i] = 0x60FFFFFF;
                    }
                    
                }
            }
            break;
            
        case SPELL_MELEE:
            damage = 0.5 * damageModifier;
            cooldown = 0.2;
            manaCost = 0;
            spellTicks = 6;
            renderOverPlayer = false;
            spellsurface = IMG_Load(GET_TEXTURE_PATH("player/spellAnimation_meleeAttack"));
            
        default:
            break;
    }
    spelltexture = getTexture(spellsurface);
}

bool Spell::castSpell(DIRECTION direction)
{
    
    //here a Projectile of the spellspecific kind should be created
    //return false if the spell is on cooldown
    castDirection = direction;
    switch (direction) {
        case UP:
            xDir = 0;
            yDir = -1;
            break;
        case RIGHT:
            xDir = 1;
            yDir = 0;
            break;
        case DOWN:
            xDir = 0;
            yDir = 1;
            break;
        case LEFT:
            xDir = -1;
            yDir = 0;
        default:
            break;
    }
    
    //initial cast
    if (cooldownTimer == 0 && level->getLocalPlayer()->currentMana >= manaCost)
    {
        cooldownTimer = cooldown;
        spellTicksPassed = 0;
        switch (spellID)
        {
            //the dash spell
            case SPELL_DASH:
                level->getLocalPlayer()->currentMana -= manaCost;
                break;
            case SPELL_TEST:
                printf("FUS RO DAH\n");
                break;
                
            case SPELL_MELEE:
                //maybe stop player movement
                break;
            default:
                break;
        }
        return true;
    }
    return false;
}

void Spell::update()
{
    //shall we update the cooldown based on the frame counts? - so this should be called every frame
    if (cooldownTimer != 0)
    {
        cooldownTimer -= 1.0f / 60.0f;
        if (cooldownTimer < 0)
        {
            cooldownTimer = 0;
        }
    }
    
    //update Spells
    if (spellTicksPassed < spellTicks) {
        spellTicksPassed++;
        switch (spellID) {
            case SPELL_DASH:
                {
                    //dashSpell
                    level->getLocalPlayer()->updateMovement(TILE_SIZE * damage * xDir, TILE_SIZE * damage * yDir);
                    
                }
                break;
                
            case SPELL_MELEE:
                //here dmg hitbox
                
                
                break;
            default:
                break;
        }
    }
}

void Spell::render()
{
    if (spellTicksPassed < spellTicks) {
        switch (spellID) {
            case SPELL_DASH:
                {
                    //render it
                    SDL_Rect src = {32 * level->getLocalPlayer()->anim, (level->getLocalPlayer()->animSet * 4 + level->getLocalPlayer()->direction) * 64 + 1, 32, 64};
                    for (int i = spellTicks; i <= spellTicksPassed; i--) {
                        SDL_Rect dst = {static_cast<int>(PLAYER_OFFSET_X - level->getLocalPlayer()->xoff - (TILE_SIZE * damage * xDir * (spellTicks - i))), static_cast<int>(PLAYER_OFFSET_Y - level->getLocalPlayer()->yoff - PLAYER_HEIGHT - (TILE_SIZE * damage * yDir * (spellTicks - i))), PLAYER_WIDTH, 128};
                        renderWithoutShading(spelltexture, src, dst);
                    }
                }
                break;
                
            case SPELL_MELEE:
                {
                    SDL_Rect src = {64 * (spellTicksPassed - 1), 128 * castDirection, 64, 128};
                    SDL_Rect dst = {static_cast<int>(PLAYER_OFFSET_X - level->getLocalPlayer()->xoff - 64), static_cast<int>(PLAYER_OFFSET_Y - level->getLocalPlayer()->yoff - PLAYER_HEIGHT), 1 * TILE_SIZE, 2 * TILE_SIZE};
                    renderWithoutShading(spelltexture, src, dst);
                }
                
                break;
            default:
                break;
        }
    }
    
}
