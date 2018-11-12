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
#include "LevelGen.hpp"
#include "Level.hpp"

//this class will manage the level


class LevelCave {
private:
    enum Tiles
    {
        WALL = 0,
        DIRT = 1,
        ENTRANCE = 2,
        EXIT = 3,
        BASIC_ENEMY
    };
    
    int floor = 0;
    int width = 50, height = 50;
    Level *&level;
	Window *window;
    bool entranceSet = false, exitSet = false;
    
public:
    
    LevelCave(Level *&plevel, Window *window);
    void startCave();
    void nextLevel();
};


#endif /* LevelCave_hpp */
