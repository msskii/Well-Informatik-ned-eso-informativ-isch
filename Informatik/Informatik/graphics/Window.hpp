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
#include "../level/Level.hpp"
#include "../level/loader/LevelLoader.hpp"
#include "../entity/Player.hpp"

#include "overlay/Menu.hpp"
#include "overlay/MainMenu.hpp"

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
    const uint8_t *keyStates;
    
    Menu *menu = new MainMenu();
    Level *level;
    
    bool running = false;
    
public:
    
    Window();
    void runGameLoop();
    
    void openMenu(Menu *menu);
    
    void update();
    void render(SDL_Renderer *renderer);
    
    inline void stopGameLoop() { running = false; }
};

#endif /* Window_hpp */
