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

int event_id_counter = 0;
std::map<int, Event*> eventList;

Event::Event(SerializedEvent eventData, uint8_t *args) : event_id(event_id_counter++), arguments(args)
{
    arguments = args;
    toStore = eventData;
    onTrigger = resolveFunction(toStore.event_action);
    
    eventList[event_id] = this;
}

Event::Event(int id, SerializedEvent stored, uint8_t *args) : event_id(id), toStore(stored), arguments(args)
{
    onTrigger = resolveFunction(toStore.event_action);
    eventList[event_id] = this;
}

void Event::trigger(Event event, EVENT_TYPE type, Level *level, uint8_t *arguments)
{
    // TODO: Check dependency & amount
    state.timesTriggered++;
    if(state.timesTriggered > toStore.triggerAmount && toStore.triggerAmount != 0) return; // Don't execute, already too much
    onTrigger(event, type, level, arguments);
}

void Event::render(SDL_Renderer *renderer, int xoffset, int yoffset)
{
    if(state.timesTriggered > toStore.triggerAmount && toStore.triggerAmount != 0) return;
    
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_Rect r = {toStore.event_x + xoffset + PLAYER_OFFSET_X, toStore.event_y + yoffset + PLAYER_OFFSET_Y, toStore.event_w, toStore.event_h};
    SDL_RenderFillRect(renderer, &r);
}
