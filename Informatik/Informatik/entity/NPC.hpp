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
#include "../util/SDL_Util.hpp"
#include <vector>
typedef struct NPCAnimation
{
    bool canWalk;
    int frameCount;
    int anim = 0;
    int timer = 0;
    int set = 0;
    int timePerFrame;
}NPCAnimation;

typedef struct NPCText
{
    
    uint32_t timesDisplayed;
    uint32_t eventTriggered;
    char *text;
    
} NPCText;

class NPC : public Entity
{
public:
    Event *event = nullptr; // The event this npc carries around
    
    std::vector<NPCText> texts;
    unsigned int currentNumTriggered = 0;
    int currentText = 0;
    
    float walking_speed = SPEED;
    NPCAnimation animation;
    
    void onInteractWith(); // Facing this npc & pressed a / space (or whatever)

    // Overrides
    void onAddToLevel(Level *level) override;
    void render(int xoff, int yoff) override;
    void update(const uint8_t *keys) override;
    void setTexture();
    
    NPC(float xPos, float yPos, int ID, int level);
    
private:
    
    SDL_Surface *NPC_surface = nullptr;
    gl_texture texture;
};

#endif /* NPC_hpp */
