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
        case TELEPORT_PLAYER:
            return teleport_player;
        case CAVE_NEXT_LEVEL:
            return cave_next_level;
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
            level->getLocalPlayer()->data.y_pos -= args[1];
            break;
        case DOWN:
            level->getLocalPlayer()->data.y_pos += args[1];
            break;
        case LEFT:
            level->getLocalPlayer()->data.x_pos -= args[1];
            break;
        case RIGHT:
            level->getLocalPlayer()->data.x_pos += args[1];
            break;
    }
}

void teleport_player(Event *event, EVENT_TYPE type, Level* level, uint8_t *args)
{
    float xpos = ((float*)args)[0];
    float ypos = ((float*)args)[1];
    uint8_t mapnum = args[8];
    
    level->setLevelMap(mapnum);
    level->getLocalPlayer()->data.x_pos = xpos;
    level->getLocalPlayer()->data.y_pos = ypos;
    level->getLocalPlayer()->updateMovement(0, 0);
}

void npc_interact(Event *event, EVENT_TYPE type, Level *level, uint8_t *args)
{
    ((NPC*)args)->onInteractWith();
}

void cave_next_level(Event *event, EVENT_TYPE type, Level *level, uint8_t *args)
{
    level->window->cave->nextLevel(level);
}
