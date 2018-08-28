//
//  NPC.hpp
//  Informatik
//
//  Created by Keanu Gleixner on 27.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef NPC_hpp
#define NPC_hpp

#include "Entity.hpp"
#include "../level/Event.hpp"
#include "Player.hpp"

class NPC : public Entity
{
public:
    Event *event = nullptr; // The event this npc carries around
    int numsTriggered = 0;
    
    void onInteractWith(); // Facing this npc & pressed a / space (or whatever)

    // Overrides
    void onAddToLevel(Level *level) override;
    void render(SDL_Renderer *renderer, int xoff, int yoff) override;
    void update(const uint8_t *keys) override;
    
    NPC(float xPos, float yPos, int level);
};

#endif /* NPC_hpp */
