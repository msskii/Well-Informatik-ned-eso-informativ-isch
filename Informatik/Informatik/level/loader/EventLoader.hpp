//
//  EventLoader.hpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef EventLoader_hpp
#define EventLoader_hpp

#include "../Level.hpp"
#include "../../util/Logger.hpp"

namespace Loader
{
    extern void saveEventData(uint8_t *destination, std::vector<Event*> events);
    extern std::vector<Event*> loadEventData(uint8_t *destination);
}

#endif /* EventLoader_hpp */
