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

class Spell
{
protected:
    
public:
    bool renderOverPlayer;
    int xDir = 0, yDir = 0;
    Level *level;
    float cooldown, damage, cooldownTimer, manaCost;
    int spellID;
    int remainingTicks, spellTicks;
    SDL_Surface *spellsurface;
    gl_texture spelltexture;
    
    Spell();
    Spell(uint8_t spellID, float damageModifier, Level *level);

    bool castSpell(int direction);
    void update();
    void render();
   
};


#endif /* Spell_hpp */
