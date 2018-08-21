//
//  Event.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Event_hpp
#define Event_hpp

enum EVENT_TYPE
{
    ALL_EVENTS = 0, // Doesn't matter what event happened
    STEP_ON, // Player steppen on it
    GAME_LOOP, // Player is in the same room
    PLAYER_INTERACT // Player interacted with it
};

typedef void (*eventFunc)(int x, int y, EVENT_TYPE type);
extern int event_id_counter;

class Event
{
public:
    eventFunc onTrigger = nullptr;
    EVENT_TYPE filter = ALL_EVENTS;
    
public:
    int event_id;
    
    Event(EVENT_TYPE type, eventFunc func);
    Event(int event_id, EVENT_TYPE type, eventFunc func);
};

typedef struct SerializedEvent
{
    int event_id;
    int event_type_filter; // The filter which is EVENT_TYPE
} SerializedEvent;

#endif /* Event_hpp */
