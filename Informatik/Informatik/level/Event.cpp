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

Event::Event(SerializedEvent eventData, uint8_t *args) : event_id(event_id_counter++), arguments(args)
{
    arguments = args;
    toStore = eventData;
    onTrigger = resolveFunction(toStore.event_action);
}

Event::Event(int id, SerializedEvent stored, uint8_t *args) : event_id(id), toStore(stored), arguments(args)
{
    onTrigger = resolveFunction(toStore.event_action);
}
