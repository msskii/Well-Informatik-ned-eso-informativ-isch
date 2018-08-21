//
//  EventLoader.cpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "EventLoader.hpp"

#include "EventActions.hpp"

void saveEventData(uint8_t *destination, std::vector<Event> events)
{
    ((uint32_t*)destination)[0] = (uint32_t) events.size(); // Maximum of 2^32 events... I think that's enough
    destination += 4; // uint32_t = 4 bytes
    for(int i = 0; i < events.size(); i++)
    {
        ((SerializedEvent*) destination)[0].event_x = events[i].x;
        ((SerializedEvent*) destination)[0].event_y = events[i].y;
        ((SerializedEvent*) destination)[0].event_type_filter = events[i].filter;
        ((SerializedEvent*) destination)[0].event_action = events[i].event_action;
        ((SerializedEvent*) destination)[0].event_id = events[i].event_id;

        // Copy parameters
        memcpy(destination + sizeof(SerializedEvent), events[i].arguments, NUM_ARGS[events[i].event_action]);
        
        destination += sizeof(SerializedEvent) + NUM_ARGS[events[i].event_action];
    }
}

std::vector<Event> loadEventData(uint8_t *destination)
{
    std::vector<Event> events;
    
    uint32_t size = ((uint32_t*)destination)[0];
    printf("We have %d events\n", size);
    destination += 4; // uint32_t = 4 bytes
    for(int i = 0; i < size; i++)
    {
        
        SerializedEvent evt = ((SerializedEvent*) destination)[0];
        uint8_t num_args = NUM_ARGS[evt.event_action];

        printf("Loading Event: %d, with action: %d & argslength: %d\n", evt.event_id, evt.event_action, NUM_ARGS[evt.event_action]);
        
        Event e(evt.event_id, (EVENT_TYPE) evt.event_type_filter, evt.event_action);
        e.x = evt.event_x;
        e.y = evt.event_y;
        e.arguments = (uint8_t*) malloc(num_args);
        memcpy(e.arguments, destination + sizeof(SerializedEvent), num_args);
        
        events.push_back(e);
        destination += sizeof(SerializedEvent) + num_args;
    }
    
    return events;
}
