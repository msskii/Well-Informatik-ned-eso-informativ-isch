//
//  Event.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Event.hpp"

#include "loader/EventActions.hpp"
#include "../entity/Player.hpp"

int event_id_counter = 1; // Start with id Nr. 1
std::map<int, int> eventTriggerCounter;

Event::Event(EventData eventData, uint8_t *args) : arguments(args)
{
    event_data = eventData;
    onTrigger = resolveFunction(event_data.event_action);
    
    if(event_data.event_id == 0) event_data.event_id = event_id_counter++; // Auto-increment
    printf("[INFO] Created event with id: %d\n", event_data.event_id);
    
    eventTriggerCounter[event_data.event_id] = 0; // This event was executed 0 times
}

void Event::trigger(EVENT_TYPE type, Level *level)
{
    if(eventTriggerCounter[event_data.event_id] > event_data.triggerAmount && event_data.triggerAmount != 0) return; // Don't execute, already too much
    if(event_data.event_id_dependency != 0 && eventTriggerCounter[event_data.event_id_dependency] == 0) return;
    
    eventTriggerCounter[event_data.event_id]++;
    onTrigger(this, type, level, arguments);
}

void Event::render(SDL_Renderer *renderer, int xoffset, int yoffset)
{
    if(eventTriggerCounter[event_data.event_id] >= event_data.triggerAmount && event_data.triggerAmount != 0) return;
    if(event_data.event_id_dependency != 0 && eventTriggerCounter[event_data.event_id_dependency] == 0) return;
    
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x55);
    SDL_Rect r = {event_data.event_x + xoffset + PLAYER_OFFSET_X, event_data.event_y + yoffset + PLAYER_OFFSET_Y, event_data.event_w, event_data.event_h};
    SDL_RenderFillRect(renderer, &r);
}
