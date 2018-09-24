//
//  NPC.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 27.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "NPC.hpp"
#include "../level/Level.hpp"

NPC::NPC(float xPos, float yPos, int level)
{
    printf("[INFO] Created new NPC at %.8f %.8f\n", xPos, yPos);
    
    data.x_pos = xPos;
    data.y_pos = yPos;
    
    EventData evt;
    evt.event_x = (int)(xPos - PLAYER_WIDTH);
    evt.event_y = (int)(yPos - PLAYER_HEIGHT);
    evt.event_w = 3 * PLAYER_WIDTH;
    evt.event_h = 3 * PLAYER_HEIGHT;
    
    evt.event_id_dependency = 0; // No dependency
    evt.triggerAmount = 0; // Infinite amounts
    
    evt.event_type_filter = PLAYER_INTERACT;
    evt.event_action = NPC_INTERACT;
    evt.event_id = 0;
    
    event = new Event(evt, (uint8_t*) this);
    event->isStored = false; // Don't store it in the level file
}

void NPC::onInteractWith()
{
    bool isFacingMe = false;
    
    isFacingMe |= level->getPlayer()->data.x_pos + PLAYER_WIDTH / 2 < data.x_pos + data.width / 2 && level->getPlayer()->direction == RIGHT;
    isFacingMe |= level->getPlayer()->data.x_pos + PLAYER_WIDTH / 2 > data.x_pos + data.width / 2  && level->getPlayer()->direction == LEFT;
    isFacingMe |= level->getPlayer()->data.y_pos + PLAYER_HEIGHT / 2 < data.y_pos + data.height / 2 + data.height && level->getPlayer()->direction == DOWN;
    isFacingMe |= level->getPlayer()->data.y_pos + PLAYER_HEIGHT / 2 > data.y_pos + data.height / 2 && level->getPlayer()->direction == UP;

    if(isFacingMe && currentText < (int) texts.size())
    {
        NPCText text = texts[currentText];
        level->window->openMenu(new DialogOverlay(text.text));
        
        if(text.eventTriggered > 0)
        {
            for(int i = 0; i < (int) level->events.size(); i++)
            {
                if(text.eventTriggered == level->events[i]->event_data.event_id) level->events[i]->trigger(NPC_FINISHED_TALKING, level);
            }
        }
        
        if(++currentNumTriggered >= text.timesDisplayed && text.timesDisplayed > 0)
        {
            ++currentText;
            currentNumTriggered = 0;
        }
    }
}

void NPC::render(int xoff, int yoff)
{
    // Simulate random movement. Doesn't check collision --> very buggy, just to test that the event moves with the entity
    //data.x_pos += (rand() % 3) - 1;
    //data.y_pos += (rand() % 3) - 1;

    //COLOR(renderer, 0xFF000000);
    SDL_Rect r = getBoundingBox();
    TRANSFORM_LEVEL_POS(r, xoff, yoff);
    //SDL_RenderFillRect(renderer, &r);
    fillRect(0xFF000000, r);
}

void NPC::update(const uint8_t *keys)
{
    event->event_data.event_x = (int)(data.x_pos - PLAYER_WIDTH);
    event->event_data.event_y = (int)(data.y_pos - PLAYER_HEIGHT);
}

void NPC::onAddToLevel(Level *l)
{
    level->events.push_back(event); // Add the event to the level
}
