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
    INFO_VAR("Saving Event data for ");
    PRINT_INT((int) events.size());
    PRINT_STRING(" events\n");

    ((uint32_t*)destination)[0] = (uint32_t) events.size(); // Maximum of 2^32 events... I think that's enough
    destination += 4; // uint32_t = 4 bytes
    for(int i = 0; i < events.size(); i++)
    {
        ((SerializedEvent*) destination)[0] = events[i].toStore;

        // Copy parameters
        memcpy(destination + sizeof(SerializedEvent), events[i].arguments, NUM_ARGS[events[i].toStore.event_action]);
        
        destination += sizeof(SerializedEvent) + NUM_ARGS[events[i].toStore.event_action];
    }
}

std::vector<Event> loadEventData(uint8_t *destination)
{
    std::vector<Event> events;
    
    uint32_t size = ((uint32_t*)destination)[0];
    
    INFO_VAR("Loading Event data for ");
    PRINT_INT(size);
    PRINT_STRING(" events\n");
    
    destination += 4; // uint32_t = 4 bytes
    for(int i = 0; i < size; i++)
    {
        
        SerializedEvent evt = ((SerializedEvent*) destination)[0];
        uint8_t num_args = NUM_ARGS[evt.event_action];

        printf("[INFO] Loading Event: %d, with action: %d & argslength: %d\n", evt.event_id, evt.event_action, NUM_ARGS[evt.event_action]);
        
        uint8_t *arguments = (uint8_t*) malloc(num_args);
        memcpy(arguments, destination + sizeof(SerializedEvent), num_args);
        Event e(evt.event_id, evt, arguments);

        events.push_back(e);
        destination += sizeof(SerializedEvent) + num_args;
    }
    
    return events;
}
