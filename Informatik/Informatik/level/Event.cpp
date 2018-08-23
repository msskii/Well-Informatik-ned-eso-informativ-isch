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

Event::Event(SerializedEvent eventData, uint8_t *args) : arguments(args)
{
    toStore = eventData;
    onTrigger = resolveFunction(toStore.event_action);
    
    if(eventData.event_id == 0)eventData.event_id = event_id_counter++; // Auto-increment
    
    event_id = eventData.event_id;

    eventTriggerCounter[event_id] = 0;
}

void Event::trigger(Event event, EVENT_TYPE type, Level *level, uint8_t *arguments)
{
    if(eventTriggerCounter[event_id] > toStore.triggerAmount && toStore.triggerAmount != 0) return; // Don't execute, already too much
    if(toStore.event_id_dependency != 0 && eventTriggerCounter[toStore.event_id_dependency] == 0) return;

    eventTriggerCounter[event_id]++;
    onTrigger(event, type, level, arguments);
}

void Event::render(SDL_Renderer *renderer, int xoffset, int yoffset)
{
    if(eventTriggerCounter[event_id] > toStore.triggerAmount && toStore.triggerAmount != 0) return;
    if(toStore.event_id_dependency != 0 && eventTriggerCounter[toStore.event_id_dependency] == 0) return;
    
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_Rect r = {toStore.event_x + xoffset + PLAYER_OFFSET_X, toStore.event_y + yoffset + PLAYER_OFFSET_Y, toStore.event_w, toStore.event_h};
    SDL_RenderFillRect(renderer, &r);
}
