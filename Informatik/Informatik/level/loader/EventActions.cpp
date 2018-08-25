//
//  EventActions.cpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "EventActions.hpp"
#include "../Level.hpp"

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

void no_action(Event event, EVENT_TYPE type, Level* level, uint8_t *args)
{
    
}

void move_player(Event event, EVENT_TYPE type, Level* level, uint8_t *args)
{
    switch(args[0])
    {
        case UP:
            level->player->_y -= args[1];
            break;
        case DOWN:
            level->player->_y += args[1];
            break;
        case LEFT:
            level->player->_x -= args[1];
            break;
        case RIGHT:
            level->player->_x += args[1];
            break;
    }
    
}
