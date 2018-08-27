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

int main(int argc, char **args)
{
    // Tests::testLevelLoader();
	// Tests::testSockets();
    // Tests::testPNG();

    Window w;
    w.runGameLoop();
    return 0;
}
