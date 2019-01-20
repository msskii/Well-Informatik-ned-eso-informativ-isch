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
    SPELL_TEST,
    SPELL_DASH,
    SPELL_MELEE
};

class Spell
{
protected:
    
public:
    bool renderOverPlayer;
    int xDir = 0, yDir = 0;
    Level *level;
    float cooldown, damage, cooldownTimer = 0, manaCost;
    SpellType spellID;
    int spellTicksPassed, spellTicks;
    SDL_Surface *spellsurface;
    gl_texture spelltexture;
    DIRECTION castDirection;

    
    Spell();
    Spell(SpellType spellID, float damageModifier, Level *level);


    void update();
    void render();
    bool castSpell(DIRECTION direction);
    void updateCooldown();
   
};


#endif /* Spell_hpp */
