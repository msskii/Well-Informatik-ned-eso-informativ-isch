//
//  EventActions.hpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef EventActions_hpp
#define EventActions_hpp

#include "../Event.hpp"
#include "../../entity/NPC.hpp"

extern eventFunc resolveFunction(int action);

extern void no_action(Event *event, EVENT_TYPE type, Level *level, uint8_t *args);
extern void move_player(Event *event, EVENT_TYPE type, Level *level, uint8_t *args);
extern void teleport_player(Event *event, EVENT_TYPE type, Level *level, uint8_t *args);
extern void npc_interact(Event *event, EVENT_TYPE type, Level *level, uint8_t *args);
extern void cave_next_level(Event *event, EVENT_TYPE type, Level *level, uint8_t *args);

#endif /* EventActions_hpp */
