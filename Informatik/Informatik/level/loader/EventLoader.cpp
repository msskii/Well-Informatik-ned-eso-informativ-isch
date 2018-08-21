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
        ((SerializedEvent*) destination)[i] = {events[i].event_id, events[i].filter};
    }
}

std::vector<Event> loadEventData(uint8_t *destination)
{
    std::vector<Event> events;
    
    uint32_t size = ((uint32_t*)destination)[0];
    destination += 4; // uint32_t = 4 bytes
    for(int i = 0; i < size; i++)
    {
        SerializedEvent evt = ((SerializedEvent*) destination)[i];

        events.push_back(Event(evt.event_id, (EVENT_TYPE) evt.event_type_filter, no_action));
    }
    
    return events;
}
