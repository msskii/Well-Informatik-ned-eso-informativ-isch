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

enum EVENT_TYPE
{
    ALL_EVENTS = 0, // Doesn't matter what event happened
    STEP_ON, // Player steppen on it
    GAME_LOOP, // Player is in the same room
    PLAYER_INTERACT // Player interacted with it
};

typedef void (*eventFunc)(int x, int y, EVENT_TYPE type, uint8_t *arguments);
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

enum EVENT_ACTION
{
    NO_ACTION = 0,
    MOVE_PLAYER
};

const static uint8_t *NUM_ARGS = new uint8_t[2]
{
    0,
    2 // Direction & amount
};

typedef struct SerializedEvent // The core information of an event
{
    int event_x;
    int event_y;
    
    int event_id;
    int event_type_filter; // The filter which is EVENT_TYPE
    int event_action; // The action for this event. Number of arguments is in NUM_ARGS
} SerializedEvent;

#endif /* Event_hpp */
