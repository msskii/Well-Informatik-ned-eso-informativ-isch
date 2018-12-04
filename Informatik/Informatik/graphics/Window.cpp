//
//  Window.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Window.hpp"

Window::Window() // Load from file, or if not found w = 50 & h = 50
{
    // Load config
    reloadConfig();
 
    // Init SDL & subsystems
    SDL_Init(SDL_INIT_VIDEO | SDL_VIDEO_OPENGL | SDL_INIT_TIMER | SDL_INIT_AUDIO); // Add audio subsystem?
    initSound();
    
    // Set up GL context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); // Load GL version 3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2); // .2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); // The core profile (Macs don't have more than that above GL version 2.1)
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); // Enable accelerated graphics
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Enable double buffering (No flickering)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Set the forward compability flag (Not sure if needed, but macs seem to need it)
    
    // 8 bits per color channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    
    // Load initial width in the config
    width = loader->getInt("screen.width");
    height = loader->getInt("screen.height");
    SCALE_X = (float)width / (float)GAME_WIDTH;
    SCALE_Y = (float)height / (float)GAME_HEIGHT;
    
    // Create window
#ifdef FULLSCREEN_ENABLED
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
#else
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
#endif
    
    // Create a GL-context that gl knows that it should draw to this window
    context = SDL_GL_CreateContext(window);
    if(context == nullptr) // Check if we succeeded
    {
        printf("[ERROR] Couldn't create GL context\n");
        exit(0);
    }
    
    // Initialize Glew to set up the function pointers to the gl functions
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        printf("[ERROR] Error initializing GLEW: %s\n", glewGetErrorString(err));
        exit(0);
    }
    
    printf("[INFO] Initialized GLEW: \n\tGL   Version: %s\n\tGLSL Version: %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    SDL_GL_SetSwapInterval(1); // Enable Vsync for OpenGL
    
    if(TTF_Init() == -1) // Initialize the Font loading subsystem
    {
        printf("TTF_Init error: %s\n", TTF_GetError());
        exit(2);
    }
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG); // init the image loading part
    
    // Open the font
    font = TTF_OpenFont(GET_FILE_PATH(FONT_PATH, "Raleway-Regular.ttf"), 64); // Window opened = font initialized
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    
    // Check if the font could be created & crash if we couldnt
    if(!font)
    {
        ERROR("[ERROR] Couldn't open font file...");
        printf("%s\n", TTF_GetError());
        exit(0);
    }
    
    // Init gl
    setupGL();
    setScreenSize(width, height);
    
    // Set up level
    //check if its the cave
    //else switch from the levels
    switch(currentLevel)
    {
        case 0:
            cave = new LevelCave(level, this);
            cave->startCave();
            break;
        case 1:
            //this is map 1
            level = Loader::loadLevel(GET_FILE_PATH(LEVEL_PATH, "/testlevel.level"), 50, 50);
            break;
            
        case 2:
            //map 2 etc
            level = Loader::loadLevel(GET_FILE_PATH(LEVEL_PATH, "/testlevel.level"), 50, 50);
            break;
        default:
            break;
    }

    
    
    // Reload elements of the menu
    reloadElementTextures();
    
    // Set up keystates & level
    keyStates = SDL_GetKeyboardState(NULL); // Set the pointer to the pressed keys (Wont change, so we dont need to do this every frame)
    level->window = this; // Set the window pointer in the level to this window
    openMenu(new PlayerOverlay(level->getLocalPlayer())); // Open the overlay for the player (Health bar)
    
#ifdef DEBUG_OVERLAY
    openMenu(new DebugOverlay(level));
#endif
    
    openMenu(new MainMenu()); // Skip main menu
    
    lights.open(this); // Open the menu (LightOverlay is just a menu)
    
    // openMenu(new ClientOverlay());
    playSound("background/entrance.wav", -1);
}

Window::~Window()
{
    delete level; // Delete the level
    SDL_DestroyWindow(window); // Close the window & Delete it from memory
}

void Window::update()
{
    // Update the player's moving speeds
    float x = 0, y = 0;
    if(keyStates[SDL_GetScancodeFromKey(GLOBAL_KEY_CONFIG[BUTTON_UP])]) y -= SPEED;
    if(keyStates[SDL_GetScancodeFromKey(GLOBAL_KEY_CONFIG[BUTTON_DOWN])]) y += SPEED;
    if(keyStates[SDL_GetScancodeFromKey(GLOBAL_KEY_CONFIG[BUTTON_RIGHT])]) x += SPEED;
    if(keyStates[SDL_GetScancodeFromKey(GLOBAL_KEY_CONFIG[BUTTON_LEFT])]) x -= SPEED;
    
    level->getLocalPlayer()->updateMovement(x, y); // Update player movement
    level->getLocalPlayer()->update(keyStates);
    level->getLocalPlayer()->actionPressed = keyStates[SDL_GetScancodeFromKey(GLOBAL_KEY_CONFIG[BUTTON_INTERACT])];
    
    level->update(); // Update rest of level according to player
}

void Window::openMenu(Menu *m)
{
    m->active = true; // The newly opened menu is active
    menus.push_back(m); // Add it to our list
    m->open(this); // Open the menu
}

void Window::render()
{
    if(toUpdate) level->render(); // Render level, but don't update
    
    for(int i = 0; i < (int) menus.size(); i++)
    {
        if(menus[i]->shouldWindowClose() || menus[i]->menuShouldBeClosed) // Check if menu should be closed
        {
            if(i != 0) menus[menus.size() - 1]->active = true; // If yes, activate the one beneath it
            menus[i]->onClose(); // Close the menu
            menus.erase(menus.begin() + i); // And remove the menu from our list of opened menus
        }
        else menus[i]->render(keyStates); // Render the menu & update it with the currently pressed keys
    }
}

uint32_t secondCallback(uint32_t delay, void *args)
{
    Window* w = (Window*) args; // The window is in the args (Just need to cast it)
    w->fps = w->frames; // The current frames per second is the number of frames since the last time they were reset
    w->frames = 0; // Reset the frames
    return delay; // Set up another timer with the same delay (1 second)
}

// Starts the game
void Window::runGameLoop()
{
    running = true;
    SDL_AddTimer(1000, secondCallback, this); // Used to calculate the fps
    
    // Macos 10.14 fix
    nextFrame();
    SDL_SetWindowPosition(window, 0, 0);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    int maxSetupTime = 60 * 20; // 20 seconds
    while(running)
    {
        if(!establishingConnection) nextFrame(); // Draw next frame
        else if(!--maxSetupTime) return; // Connection failed
    }
    
    exitGame(this); // Game has finished... Exit
}

void Window::nextFrame()
{
    ++frames; // A simple frame counter
    auto start_time = clock.now(); // Now --> used to wait afterwards
    
    if(cooldown) --cooldown; // Player is in cooldown
    lights.startFrame(); // Clear the lights & prepare the lightoverlay
    
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        // Check if it was a mousepressed event even if we're already pressed or a release if we're not pressed
        if((e.type == SDL_MOUSEBUTTONDOWN && mousePressed) || (e.type == SDL_MOUSEBUTTONUP && !mousePressed)) continue;
        if(e.type == SDL_MOUSEBUTTONDOWN) mousePressed = true;
        if(e.type == SDL_MOUSEBUTTONUP) mousePressed = false;
        
        if(e.type == SDL_FINGERDOWN || e.type == SDL_FINGERUP || e.type == SDL_FINGERMOTION)
        {
            // No touch events... yet
            continue;
        }
        
        for(int i = (int) menus.size() - 1; i >= 0; i--) // Update all the elements of all menus with this event
        {
            menus[i]->updateElements(e);
            if(menus[i]->consumeEvent) // If the event was consumed, don't send the event to the menus below
            {
                menus[i]->consumeEvent = false;
                break;
            }
        }
        
        // Handle events of the window
        if(e.type == SDL_WINDOWEVENT)
        {
            if(e.window.event == SDL_WINDOWEVENT_CLOSE) running = false; // Close the game
            else if (e.window.event == SDL_WINDOWEVENT_RESIZED) // Update sizes & scales according to the window size
            {
                printf("Resized...\n");
                //return;
                SDL_GetWindowSize(window, &width, &height);
                setScreenSize(width, height);
                SCALE_X = (float)width / (float)GAME_WIDTH;
                SCALE_Y = (float)height / (float)GAME_HEIGHT;
            }
        }
        else if(e.type == SDL_QUIT) exitGame(this); // Just close the whole thing...
        
        // Player & Level control:
        if(!toUpdate) continue; // We're paused...
        
        if(e.type == SDL_KEYDOWN)
        {
            if(e.key.keysym.sym == SDLK_ESCAPE) openMenu(new PauseMenu()); // Open pause menu
            else if(e.key.keysym.sym == GLOBAL_KEY_CONFIG[BUTTON_SHOOT])
            {
                if(cooldown) continue; // Player cant shoot yet
                
                for(int i = 0; i < 5; i++) // Shoot n projectiles
                {
                    ExplodingProjectile *p = new ExplodingProjectile(NORMAL, level->getLocalPlayer()->data.x_pos, level->getLocalPlayer()->data.y_pos, (float) TO_RAD(rand() % 360));
                    level->addEntity(p);
                }
                
                cooldown = 60; // Wait a second
            }
            else if(e.key.keysym.sym == GLOBAL_KEY_CONFIG[BUTTON_INVENTORY]) openMenu(new Inventory(level->getLocalPlayer()));
        }
        else if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            if(e.button.button == SDL_BUTTON_RIGHT)
            {
                int xdif = (int) (e.button.x / SCALE_X) - PLAYER_OFFSET_X + level->getLocalPlayer()->xoff;
                int ydif = (int) (e.button.y / SCALE_Y) - PLAYER_OFFSET_Y + level->getLocalPlayer()->yoff;
                float angle = -(float) atan2(ydif, xdif); // Calculate the angle of the arrow
                
                // Shoot the arrow by spawning it
                Projectile *p = new Projectile(level->getLocalPlayer()->data.x_pos, level->getLocalPlayer()->data.y_pos, angle);
                level->addEntity(p);
            }
        }
    }
    
    // Set black as background
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Update & render
    toUpdate = true;
    for(int i = 0; i < (int) menus.size(); i++) if(!menus[i]->shouldLevelBeUpdated) toUpdate = false;
    if(toUpdate) update();
    render();
    
    // If there was an error print it
    GLenum err = glGetError();
    if(err != GL_NO_ERROR)
    {
        printf("[ERROR] GL Error: %d\n", err);
    }
    
    lights.render(); // Draw the lights (Shaders)
    
    SDL_GL_SwapWindow(window); // Make the rendered stuff appear (Because we have two buffers)
    
    // Calculate time difference and wait for the rest of the 1/60th of a second
    auto end_time = clock.now();
    auto difference = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    if(difference.count() > 0) std::this_thread::sleep_for(std::chrono::microseconds(16000) - difference);
}

// Reload the config file
void Window::reloadConfig()
{
    loader = new ConfigLoader(GET_FILE_PATH(LEVEL_PATH, "informatik.config"));
}

// Save level and quit
void exitGame(Window *window)
{
    Loader::LevelLoader loader(window->level);
    loader.saveFile(window->level->levelFile.c_str());
    
    SDL_DestroyWindow(window->window);
    SDL_Quit();
        
    exit(0);
}
