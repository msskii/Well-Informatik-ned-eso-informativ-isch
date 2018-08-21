//
//  Event.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Event.hpp"

#include "loader/EventActions.hpp"

int event_id_counter = 0;

Event::Event(EVENT_TYPE type, int action, int xc, int yc, uint8_t *args) : event_id(event_id_counter++), x(xc), y(yc), filter(type), event_action(action), onTrigger(resolveFunction(action))
{
    arguments = args;
}

Event::Event(int id, EVENT_TYPE type, int action) : event_id(id), filter(type), event_action(action), onTrigger(resolveFunction(action))
{
    arguments = (uint8_t*) malloc(NUM_ARGS[action]);
}
