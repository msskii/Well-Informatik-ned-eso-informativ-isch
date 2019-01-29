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

enum SpellType {
    SPELL_DASH = 0,
    SPELL_PUSH_BACK = 1,
    SPELL_MELEE = 2,
    SPELL_FIRESHOT = 3,
    SPELL_NONE = 4
};

class Spell
{
protected:
    
public:
    bool renderOverPlayer;
    int xDir = 0, yDir = 0;
    int spellx = 0, spelly = 0;
    double angle = 0;
    Level *level;
    float cooldown, damage, cooldownTimer = 0, manaCost;
    SpellType spellID;
    int spellTicksPassed = 0, spellTicks = 0;;
    SDL_Surface *spellsurface = nullptr;
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
