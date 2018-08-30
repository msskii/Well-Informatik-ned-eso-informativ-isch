//
//  EventData.hpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef EventData_h
#define EventData_h

#include "../../config.h"

enum EVENT_TYPE
{
    ALL_EVENTS = 0, // Doesn't matter what event happened
    STEP_ON, // Player steppen on it
    GAME_LOOP, // Player is in the same room
    PLAYER_INTERACT, // Player interacted with it
    NPC_FINISHED_TALKING // When an npc finished talking

};

// Pseudo definitions of classes
class Level;
class Event;

typedef void (*eventFunc)(Event *event, EVENT_TYPE type, Level *level, uint8_t *arguments); // How a event handler function should look like

enum EVENT_ACTION // The different actions (Add them here)
{
    NO_ACTION = 0,
    MOVE_PLAYER,
    NPC_INTERACT,
};

const static uint8_t *NUM_ARGS = new uint8_t[3] // how many arguments for the nth action
{
    0, // No action = No arguments
    2, // Direction & amount
    0 // Not stored...
};

#pragma pack(push, 1)
typedef struct EventData // The core information of an event
{
    int event_x = 0;
    int event_y = 0;
    
    int event_w = TILE_SIZE;
    int event_h = TILE_SIZE;
    
    int triggerAmount = 0; // How many times the event can be triggered
    int event_id_dependency = 0; // Which event needs to be executed that this one becomes active
    
    int event_id = 0;
    EVENT_TYPE event_type_filter = STEP_ON; // The filter which is EVENT_TYPE
    EVENT_ACTION event_action = NO_ACTION; // The action for this event. Number of arguments is in NUM_ARGS
} EventData;
#pragma pack(pop)

#endif /* EventData_h */
