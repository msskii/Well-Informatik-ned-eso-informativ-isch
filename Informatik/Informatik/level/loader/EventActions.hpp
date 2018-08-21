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

extern eventFunc resolveFunction(int action);

extern void no_action(int x, int y, EVENT_TYPE type, uint8_t *args);
extern void move_player(int x, int y, EVENT_TYPE type, uint8_t *args);

#endif /* EventActions_hpp */
