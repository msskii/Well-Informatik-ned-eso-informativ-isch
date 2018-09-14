//
//  EventLoader.cpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "EventLoader.hpp"

#include "EventActions.hpp"

void Loader::saveEventData(uint8_t *destination, std::vector<Event*> events)
{
    int numEvents = 0;
    for(int i = 0; i < (int) events.size(); i++)
    {
        if(events[i]->isStored) ++numEvents;
    }
    
    /**INFO_VAR("Saving Event data for ");
    PRINT_INT((int) numEvents);
    PRINT_STRING(" events\n");*/

    ((uint32_t*)destination)[0] = numEvents; // Maximum of 2^32 events... I think that's enough
    destination += 4; // uint32_t = 4 bytes
    for(int i = 0; i < numEvents; i++)
    {
        if(!events[i]->isStored) continue;
        
        ((EventData*) destination)[0] = events[i]->event_data;

        // Copy parameters
        memcpy(destination + sizeof(EventData), events[i]->arguments, NUM_ARGS[events[i]->event_data.event_action]);
        
        destination += sizeof(EventData) + NUM_ARGS[events[i]->event_data.event_action];
    }
}

std::vector<Event*> Loader::loadEventData(uint8_t *destination)
{
    std::vector<Event*> events;
    
    uint32_t size = ((uint32_t*)destination)[0];
    
    /**INFO_VAR("Loading Event data for ");
    PRINT_INT(size);
    PRINT_STRING(" events\n");*/
    
    event_id_counter = 0; // Start at event 0 again...
    
    destination += 4; // uint32_t = 4 bytes
    for(int i = 0; i < (int)size; i++)
    {
        
        EventData evt = ((EventData*) destination)[0];
        uint8_t num_args = NUM_ARGS[evt.event_action];

        //printf("[INFO] Loading Event: %d, with action: %d & argslength: %d\n", evt.event_id, evt.event_action, NUM_ARGS[evt.event_action]);
        
        uint8_t *arguments = (uint8_t*) malloc(num_args);
        memcpy(arguments, destination + sizeof(EventData), num_args);
        Event *e = new Event(evt, arguments);

        events.push_back(e);
        destination += sizeof(EventData) + num_args;
    }
    
    return events;
}
