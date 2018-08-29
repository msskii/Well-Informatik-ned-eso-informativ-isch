//
//  NPCLoader.hpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef NPCLoader_hpp
#define NPCLoader_hpp

#include "../../util/FileReader.hpp"
#include "../NPC.hpp"

namespace Loader
{
    extern std::vector<Entity*> loadNPCs(const char *filepath);
    extern Entity* loadNPC(uint8_t *&data);
}

#endif /* NPCLoader_hpp */
