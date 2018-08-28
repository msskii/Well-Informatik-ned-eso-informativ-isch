//
//  NPC.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 27.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "NPC.hpp"


NPC::NPC(float xPos, float yPos, int level)
{
    data.x_pos = xPos;
    data.y_pos = yPos;
    
    EventData evt;
    evt.event_x = xPos - PLAYER_WIDTH;
    evt.event_y = yPos - PLAYER_HEIGHT;
    evt.event_w = 3 * PLAYER_WIDTH;
    evt.event_h = 3 * PLAYER_HEIGHT;
    
    evt.event_id_dependency = 0; // No dependency
    evt.triggerAmount = 0; // Infinite amounts
    
    evt.event_type_filter = PLAYER_INTERACT;
    evt.event_action = NPC_INTERACT;
    
    event = new Event(evt, (uint8_t*) this);
    event->isStored = false; // Don't store it in the level file
}

void NPC::onInteractWith()
{
    bool isFacingMe = false;
    
    isFacingMe |= level->player->x_pos + PLAYER_WIDTH / 2 < data.x_pos + data.width / 2 && level->player->direction == RIGHT;
    isFacingMe |= level->player->x_pos + PLAYER_WIDTH / 2 > data.x_pos + data.width / 2  && level->player->direction == LEFT;
    isFacingMe |= level->player->y_pos + PLAYER_HEIGHT / 2 < data.y_pos + data.height / 2 + data.height && level->player->direction == DOWN;
    isFacingMe |= level->player->y_pos + PLAYER_HEIGHT / 2 > data.y_pos + data.height / 2 && level->player->direction == UP;

    if(isFacingMe && currentText < (int) texts.size())
    {
        NPCText text = texts[currentText];
        level->window->openMenu(new DialogOverlay(text.text));
        
        if(++currentNumTriggered >= text.timesDisplayed && text.timesDisplayed > 0)
        {
            ++currentText;
            currentNumTriggered = 0;
        }
    }
}

void NPC::render(SDL_Renderer *renderer, int xoff, int yoff)
{
    // Simulate random movement. Doesn't check collision --> very buggy, just to test that the event moves with the entity
    //data.x_pos += (rand() % 3) - 1;
    //data.y_pos += (rand() % 3) - 1;

    COLOR(renderer, 0xFF000000);
    SDL_Rect r = {(int) data.x_pos + xoff + PLAYER_OFFSET_X, (int) data.y_pos + yoff + PLAYER_OFFSET_Y, 50, 50};
    SDL_RenderFillRect(renderer, &r);
}

void NPC::update(const uint8_t *keys)
{
    event->event_data.event_x = data.x_pos - PLAYER_WIDTH;
    event->event_data.event_y = data.y_pos - PLAYER_HEIGHT;
}

void NPC::onAddToLevel(Level *l)
{
    level->events.push_back(event); // Add the event to the level
}
