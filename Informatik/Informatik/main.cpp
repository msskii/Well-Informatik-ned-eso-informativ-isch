//
//  main.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include <iostream>
#include "graphics/Window.hpp"
#include "util/FileReader.hpp"

#include "tests/Tests.hpp"
#include "multiplayer/Server.hpp"

void startGame()
{
#ifdef DEBUG_RANDOM
    srand(0);
#else
    srand((int) time(NULL)); // Enable to get differen shades each time
#endif
    
    Window w;
    // Time to inject stuff into the level
    
    w.runGameLoop();
}

int main(int argc, char **args)
{
    // Tests::testLevelLoader();
	// Tests::testSockets();
    // Tests::testPNG();
    // Tests::testTextLoader();
    // Tests::testNPCLoader();
        
    startGame();
    //Multiplayer::Server s;
    
    return 0;
}
