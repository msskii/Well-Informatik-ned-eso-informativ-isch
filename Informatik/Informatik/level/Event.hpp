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

#include <map>

#include "../util/SDL_Util.hpp"
#include "loader/EventData.hpp"

class Event
{
public:
    eventFunc onTrigger = nullptr; // What does this event do
    
public:
    
    uint8_t *arguments; // The arguments for this event
    SerializedEvent toStore; // The actual event
    
public:
    int event_id;
    
    Event(SerializedEvent eventData, uint8_t *args);
    
    void trigger(Event event, EVENT_TYPE type, Level *level, uint8_t *arguments);
    void render(SDL_Renderer *renderer, int xoff, int yoff);
};



#endif /* Event_hpp */
