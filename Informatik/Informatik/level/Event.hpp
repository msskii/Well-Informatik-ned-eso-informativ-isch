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
    STEP_IN, // Player steppen on it
    GAME_LOOP, // Player is in the same room
    PLAYER_INTERACT // Player interacted with it
};

typedef void (*eventFunc)(int x, int y, EVENT_TYPE type);

class Event
{
private:
    
    
public:
};

#endif /* Event_hpp */
