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
#include "../level/LevelCave.hpp"

#include "../entity/Player.hpp"
#include "../entity/NPC.hpp"
#include "../entity/decorativeEntities/Fireflies.hpp"

#include "../enemy/Slime.hpp"

#include "../projectile/Projectile.hpp"
#include "../projectile/ExplodingProjectile.hpp"

#include "../items/EntityItem.hpp"

#include "../multiplayer/ClientOverlay.hpp"

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
#include "../sound/SoundHandler.hpp"

class LevelCave;

class Window
{
public:
    SDL_Window *window; // The actual window
    SDL_GLContext context; // The gl context
    int width = WINDOW_WIDTH, height = WINDOW_HEIGHT; // The size of the window
    const uint8_t *keyStates; // A pointer to all the keys and their current state (Pressed or not)
    int cooldown = 0; // The cooldown of the player until he can shoot again
    
    LightOverlay lights = LightOverlay(); // The handler for the lights
    
    ConfigLoader *loader = nullptr; // Configloader to load the config file
    std::chrono::high_resolution_clock clock = std::chrono::high_resolution_clock(); // Create high accuracy clock
    bool mousePressed = false; // If the mouse is currently pressed or not
    
    std::vector<Menu*> menus; // All open menus
    Level *level; // The current level we're in
    LevelCave *cave; //cave Object if we're in a cave
    bool toUpdate = true; // If we have to update the level or not
    bool establishingConnection = false;
    int currentLevel = 0;
    
    int frames = 0, fps = 0; // The current frames and the last measured FPS
    
    bool running = false; // If we're running or not (Window will be closed if false)
public:
    
    Window(); // Constructor: Sets up all the things!
    ~Window(); // Destructor: Clears all the things?
    
    void nextFrame(); // Draw the next frame
    void runGameLoop(); // Function that calls nextFrame contiously and checks if we're still running
    
    void openMenu(Menu *menu); // Open a new menu
    
    void update(); // Updates the player
    void render(); // Renders the menus & level
    
    void reloadConfig(); // Reloads the config file
    
    inline void stopGameLoop() { running = false; } // Stop the game from running (Equivalent to just setting running to false)
};

extern void exitGame(Window *window);
extern void openMenu(Menu *menu);

#endif /* Window_hpp */
