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
    eventFunc onTrigger = nullptr; // What does this event do
    
    uint8_t *arguments; // The arguments for this event
    SerializedEvent toStore; // The actual event
    
public:
    int event_id;
    
    Event(SerializedEvent eventData, uint8_t *args);
    Event(int id, SerializedEvent stored, uint8_t *args);
};



#endif /* Event_hpp */
