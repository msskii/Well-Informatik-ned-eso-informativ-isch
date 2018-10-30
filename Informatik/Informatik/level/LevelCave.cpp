//
//  LevelCave.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 30.10.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "LevelCave.hpp"

LevelCave::LevelCave(Level *level)
{
    
}

*Level LevelCave::nextLevel()
{
    floor++;
    Level level = new Level(width, height);
    return level;
}
