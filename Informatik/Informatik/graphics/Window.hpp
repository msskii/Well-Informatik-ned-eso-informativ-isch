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
#include "../entity/NPC.hpp"

#include "../enemy/Slime.hpp"

#include "../projectile/Projectile.hpp"

#include "../items/EntityItem.hpp"

#include "overlay/Menu.hpp"
#include "overlay/MainMenu.hpp"
#include "overlay/DebugOverlay.hpp"
#include "overlay/DialogOverlay.hpp"
#include "overlay/PauseMenu.hpp"
#include "gui/Inventory.hpp"

#include <time.h>
#include <thread>
#include <chrono>


#include "../util/SDL_Util.hpp"

class Window
{
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    const uint8_t *keyStates;
    
    // Menu *menu = new MainMenu();
    std::vector<Menu*> menus; // All open menus
    Level *level;
    bool toUpdate = true;
    
    int frames = 0, fps = 0;
    uint64_t lastTime = time(NULL);
    
    bool running = false;
    bool paused = false;
public:
    
    Window();
    ~Window();
    void runGameLoop();
    
    void openMenu(Menu *menu);
    
    void update();
    void render(SDL_Renderer *renderer);
    
    inline void stopGameLoop() { running = false; }
};

extern void openMenu(Menu *menu);

#endif /* Window_hpp */
