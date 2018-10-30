//
//  LevelCave.hpp
//  Informatik
//
//  Created by Keanu Gleixner on 30.10.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef LevelCave_hpp
#define LevelCave_hpp

#include <stdio.h>
#include "Level.hpp"

//this class will manage the level

class LevelCave {
    int floor = 1;
    int width = 50, height = 50;
    
public:
    LevelCave(Level *level);
    Level nextLevel();
};


#endif /* LevelCave_hpp */
