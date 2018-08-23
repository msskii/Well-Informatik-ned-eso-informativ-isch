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

int main(int argc, char **args)
{
    // LevelLoader("testlevel.level"); // Test loading level
    
    Window w;
    w.runGameLoop();
    return 0;
}
