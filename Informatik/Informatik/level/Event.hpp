//
//  Event.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Event_hpp
#define Event_hpp

#include <stdint.h>
#include <stdlib.h>

#include "loader/EventData.hpp"

extern int event_id_counter;

class Event
{
public:
    int x, y;
    eventFunc onTrigger = nullptr; // What does this event do
    EVENT_TYPE filter = ALL_EVENTS; // When is this event triggered
    int event_action = 0; // The action of this event
    uint8_t *arguments; // The arguments for this event
    
public:
    int event_id;
    
    Event(EVENT_TYPE type, int action, int x, int y, uint8_t *args);
    Event(int id, EVENT_TYPE type, int action);
};



#endif /* Event_hpp */
