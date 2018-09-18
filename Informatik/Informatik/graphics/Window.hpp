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
#include "../projectile/ExplodingProjectile.hpp"

#include "../items/EntityItem.hpp"

#include "overlay/Menu.hpp"
#include "overlay/MainMenu.hpp"
#include "overlay/DebugOverlay.hpp"
#include "overlay/DialogOverlay.hpp"
#include "overlay/PauseMenu.hpp"
#include "overlay/LightOverlay.hpp"
#include "gui/Inventory.hpp"
#include "gui/PlayerOverlay.hpp"

#include <time.h>
#include <thread>
#include <chrono>

#include "../config/ConfigLoader.hpp"

#include "../util/SDL_Util.hpp"

class Window
{
public:
    SDL_Window *window;
    SDL_Surface *render_surface = nullptr;
    SDL_Renderer *renderer;
    SDL_GLContext context;
    const uint8_t *keyStates;
    
    ConfigLoader *loader = nullptr;
    
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
    
    void reloadConfig();
    
    inline void stopGameLoop() { running = false; }
};

extern void exitGame(Window *window);
extern void openMenu(Menu *menu);

#endif /* Window_hpp */
