//
//  Tests.hpp
//  Informatik
//
//  Created by Aaron Hodel on 25.08.18.
//  Copyright � 2018 Aaron Hodel. All rights reserved.
//

#ifndef Tests_hpp
#define Tests_hpp

#include "../util/SDL_Util.hpp"
#include "../level/loader/LevelLoader.hpp"
#include "../level/loader/TextLoader.hpp"
#include "../entity/loader/NPCLoader.hpp"
#include "../multiplayer/Server.hpp"
#include "../config/ConfigLoader.hpp"

namespace Tests
{
	extern void testAudio();
	extern void testSockets();
	extern void testLevelLoader();
    extern void testTextLoader();
    extern void testNPCLoader();

    extern void testPNG();
    
    extern void testConfig();
}


#endif
