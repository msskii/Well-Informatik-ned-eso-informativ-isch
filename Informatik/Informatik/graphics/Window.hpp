//
//  Window.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include "../config.h"

#ifdef __APPLE__
#  include <SDL2/SDL.h> // Other path than on windows
#else
#  include <SDL2.h>
#endif

class Window
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    
    bool running = false;
    
public:
    
    Window();
    void runGameLoop();
    inline void stopGameLoop() { running = false; }
};

#endif /* Window_hpp */
