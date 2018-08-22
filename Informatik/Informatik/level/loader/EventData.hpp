//
//  EventData.hpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef EventData_h
#define EventData_h

enum EVENT_TYPE
{
    ALL_EVENTS = 0, // Doesn't matter what event happened
    STEP_ON, // Player steppen on it
    GAME_LOOP, // Player is in the same room
    PLAYER_INTERACT // Player interacted with it
};

// Pseudo definitions of classes
class Level;
class Event;

typedef void (*eventFunc)(Event event, EVENT_TYPE type, Level *level, uint8_t *arguments); // How a event handler function should look like

enum EVENT_ACTION // The different actions (Add them here)
{
    NO_ACTION = 0,
    MOVE_PLAYER
};

const static uint8_t *NUM_ARGS = new uint8_t[2] // how many arguments for the nth action
{
    0, // No action = No arguments
    2 // Direction & amount
};

typedef struct SerializedEvent // The core information of an event
{
    int event_x;
    int event_y;
    
    int event_w;
    int event_h;
    
    int event_id;
    int event_type_filter; // The filter which is EVENT_TYPE
    int event_action; // The action for this event. Number of arguments is in NUM_ARGS
} SerializedEvent;

#endif /* EventData_h */
