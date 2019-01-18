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
        case SPELL_TEST:
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
            spelltexture = getTexture(spellsurface);
            break;
            
        default:
            break;
    }
}

bool Spell::castSpell(DIRECTION direction)
{
    //here a Projectile of the spellspecific kind should be created
    //return false if the spell is on cooldown
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
        switch (spellID)
        {
            //the dash spell
            case SPELL_DASH:
                remainingTicks = spellTicks;
                level->getLocalPlayer()->currentMana -= manaCost;
                break;
            case SPELL_TEST:
                printf("FUS RO DAH\n");
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
    if (remainingTicks > 0) {
        remainingTicks--;
        switch (spellID) {
            case 0:
                {
                    //dashSpell
                    level->getLocalPlayer()->updateMovement(TILE_SIZE * damage * xDir, TILE_SIZE * damage * yDir);
                    
                }
                
                break;
            default:
                break;
        }
    }
}

void Spell::render()
{
    if (remainingTicks > 0) {
        switch (spellID) {
            case 0:
            {
                //render it
                SDL_Rect src = {32 * level->getLocalPlayer()->anim, (level->getLocalPlayer()->animSet * 4 + level->getLocalPlayer()->direction) * 64 + 1, 32, 64};
                for (int i = spellTicks; i >= remainingTicks; i--) {
                    SDL_Rect dst = {static_cast<int>(PLAYER_OFFSET_X - level->getLocalPlayer()->xoff - (TILE_SIZE * damage * xDir * (spellTicks - i))), static_cast<int>(PLAYER_OFFSET_Y - level->getLocalPlayer()->yoff - PLAYER_HEIGHT - (TILE_SIZE * damage * yDir * (spellTicks - i))), PLAYER_WIDTH, 128};
                    renderWithoutShading(spelltexture, src, dst);
                }
                
            }
                
                break;
            default:
                break;
        }
    }
    
}
