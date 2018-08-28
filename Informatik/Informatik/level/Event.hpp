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
    
    bool isStored = true;
    uint8_t *arguments; // The arguments for this event
    EventData event_data; // The actual event
    
public:
    int event_id;
    
    Event(EventData eventData, uint8_t *args);
        
    void trigger(EVENT_TYPE type, Level *level);
    
    void render(SDL_Renderer *renderer, int xoff, int yoff);
};



#endif /* Event_hpp */
