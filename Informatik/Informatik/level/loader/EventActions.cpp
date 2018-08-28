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
    switch(action)
    {
        case NO_ACTION:
            return no_action;
        case MOVE_PLAYER:
            return move_player;
        case NPC_INTERACT:
            return npc_interact;
        default:
            return no_action;
    }
}

void no_action(Event *event, EVENT_TYPE type, Level* level, uint8_t *args)
{
    
}

void move_player(Event *event, EVENT_TYPE type, Level* level, uint8_t *args)
{
    switch(args[0])
    {
        case UP:
            level->player->y_pos -= args[1];
            break;
        case DOWN:
            level->player->y_pos += args[1];
            break;
        case LEFT:
            level->player->x_pos -= args[1];
            break;
        case RIGHT:
            level->player->x_pos += args[1];
            break;
    }
}

void npc_interact(Event *event, EVENT_TYPE type, Level *level, uint8_t *args)
{
    ((NPC*)args)->onInteractWith();
}
