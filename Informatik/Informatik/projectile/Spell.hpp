//
//  Spell.hpp
//  Informatik
//
//  Created by Keanu Gleixner on 13.11.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Spell_hpp
#define Spell_hpp

#include <stdio.h>
#include "../level/Level.hpp"
//manages the spellSlots

enum SpellType {
    SPELL_TEST
};

class Spell
{
protected:
    
public:
    Level *level;
    float cooldown, damage, cooldownTimer;
    SpellType spellID;
    
    Spell();
    Spell(SpellType spellID, float damageModifier, Level *level);

    bool castSpell(DIRECTION direction);
    void updateCooldown();
   
};


#endif /* Spell_hpp */
