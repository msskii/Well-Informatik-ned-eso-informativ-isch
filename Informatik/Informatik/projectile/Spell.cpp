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
            damage = 10 * damageModifier;
            cooldown = 5.0;
            break;
            
        default:
            break;
    }
}

bool Spell::castSpell(DIRECTION direction)
{
    //here a Projectile of the spellspecific kind should be created
    //return false if the spell is on cooldown
    if (cooldownTimer == 0)
    {
        cooldownTimer = cooldown;
        switch (spellID)
        {
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

void Spell::updateCooldown()
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
    
}
