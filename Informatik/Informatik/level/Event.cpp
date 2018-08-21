//
//  Event.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Event.hpp"

int event_id_counter = 0;

Event::Event(EVENT_TYPE type, eventFunc func) : event_id(event_id_counter++), filter(type), onTrigger(func)
{
    
}

Event::Event(int id, EVENT_TYPE type, eventFunc func) : event_id(id), filter(type), onTrigger(func)
{
    
}
