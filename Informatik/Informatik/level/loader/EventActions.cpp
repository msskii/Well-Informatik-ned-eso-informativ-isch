//
//  EventActions.cpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "EventActions.hpp"

eventFunc resolveFunction(int action)
{
    eventFunc f = nullptr;
    
    switch(action)
    {
        case NO_ACTION:
            f = no_action;
            break;
        case MOVE_PLAYER:
            f = move_player;
            break;
        default:
            f = no_action;
            break;
    }
    
    return f;
}

void no_action(int x, int y, EVENT_TYPE type, uint8_t *args)
{
    
}

void move_player(int x, int y, EVENT_TYPE type, uint8_t *args)
{
    
}
