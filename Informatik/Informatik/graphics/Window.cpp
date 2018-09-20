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
    SDL_Init(SDL_INIT_VIDEO | SDL_VIDEO_OPENGL | SDL_INIT_TIMER); // Add audio subsystem?
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    
    // 8 bits per color channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    
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
    
    context = SDL_GL_CreateContext(window);
    if(context == nullptr)
    {
        printf("[ERROR] Couldn't create GL context\n");
        exit(0);
    }
    
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(err != GLEW_OK)
    {
        printf("[ERROR] Error initializing GLEW: %s\n", glewGetErrorString(err));
        exit(0);
    }
    
    printf("[INFO] Initialized GLEW: \n\tGL   Version: %s\n\tGLSL Version: %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    SDL_GL_SetSwapInterval(1); // Vsync
    
    if(TTF_Init() == -1)
    {
        printf("TTF_Init error: %s\n", TTF_GetError());
        exit(2);
    }
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    
    font = TTF_OpenFont(GET_FILE_PATH(FONT_PATH, "Raleway-Regular.ttf"), 64); // Window opened = font initialized
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    
    if(!font)
    {
        ERROR("Couldn't open font file...");
        printf("%s\n", TTF_GetError());
        exit(0);
    }
    
    // Set up level
    level = Loader::loadLevel(GET_FILE_PATH(LEVEL_PATH, "/testlevel.level"), 50, 50);
    
    // Reload elements of the menu
    reloadElementTextures();
    
    // Set up keystates & level
    keyStates = SDL_GetKeyboardState(NULL);
    level->window = this;
    openMenu(new PlayerOverlay(level->player));
    
    // Set up random stuff ( Debug & initial stuff on screen)
    
#ifdef DEBUG_OVERLAY
    openMenu(new DebugOverlay(level));
#endif
    
    openMenu(new MainMenu()); // Skip main menu
    // openMenu(new DialogOverlay("Hello World!\nThis is a test...\nThis is a test for very long lines\nwhich should get a line break or should\nbe newlined by hand"));
    
    NPC *npc = new NPC(TILE_SIZE * 8, TILE_SIZE * 1, 0);
    npc->texts.push_back({3, 0, (char*) "Hello World\nI mean player..."});
    npc->texts.push_back({0, 0, (char*) "Please stop talking\nto me..."});
    level->addEntity(npc);
    
    Slime *slimeg = new Slime(10 * TILE_SIZE, 5 * TILE_SIZE, 1);
    Slime *slimeb = new Slime(10 * TILE_SIZE, 15 * TILE_SIZE, 10);
    Slime *slimeo = new Slime(10 * TILE_SIZE, 25 * TILE_SIZE, 20);
    Slime *slimer = new Slime(10 * TILE_SIZE, 35 * TILE_SIZE, 30);
    level->addEntity(slimeg);
    level->addEntity(slimeb);
    level->addEntity(slimeo);
    level->addEntity(slimer);
    
    Projectile *projectile = new Projectile(0, 0, (float) PI * 15.0f / 8.0f);
    level->addEntity(projectile);
        
    for(int i = 0; i < 22; i++)
    {
        level->addEntity(new EntityItem(5, i, new Item("test")));
        level->addEntity(new EntityItem(3, i, new Item("test2")));
    }
}

Window::~Window()
{
    delete level;
    SDL_DestroyWindow(window);
}

void Window::update()
{
    // Put update stuff here
    float x = 0, y = 0;
    if(keyStates[SDL_GetScancodeFromKey(GLOBAL_KEY_CONFIG[BUTTON_UP])]) y -= SPEED;
    if(keyStates[SDL_GetScancodeFromKey(GLOBAL_KEY_CONFIG[BUTTON_DOWN])]) y += SPEED;
    if(keyStates[SDL_GetScancodeFromKey(GLOBAL_KEY_CONFIG[BUTTON_RIGHT])]) x += SPEED;
    if(keyStates[SDL_GetScancodeFromKey(GLOBAL_KEY_CONFIG[BUTTON_LEFT])]) x -= SPEED;
    
    level->player->updateMovement(x, y); // Update player movement
    level->player->actionPressed = keyStates[GLOBAL_KEY_CONFIG[BUTTON_INVENTORY]];
    
    level->update(); // Update rest of level according to player
}

void Window::openMenu(Menu *m)
{
    m->active = true;
    menus.push_back(m);
    m->open(this);
}

void Window::render()
{
    if(toUpdate) level->render(); // Render level, but don't update
    
    for(int i = 0; i < (int) menus.size(); i++)
    {
        if(menus[i]->shouldWindowClose() || menus[i]->menuShouldBeClosed)
        {
            if(i != 0) menus[menus.size() - 1]->active = true;
            menus[i]->onClose();
            menus.erase(menus.begin() + i);
        }
        else menus[i]->render(keyStates);
    }
}

uint32_t secondCallback(uint32_t delay, void *args)
{
    Window* w = (Window*) args;
    w->fps = w->frames;
    w->frames = 0;
    return delay;
}

void Window::runGameLoop()
{
    running = true;
    SDL_Event e;
    SDL_AddTimer(1000, secondCallback, this);
    
    auto clock = std::chrono::high_resolution_clock(); // Create high accuracy clock
    
    bool mousePressed = false;
    
    // Init gl
    setupGL();
    setScreenSize(width, height);
        
    openMenu(new LightOverlay());
    
    while(running)
    {
        ++frames;
        auto start_time = clock.now(); // Now
        
        while(SDL_PollEvent(&e))
        {
            if((e.type == SDL_MOUSEBUTTONDOWN && mousePressed) || (e.type == SDL_MOUSEBUTTONUP && !mousePressed))
            {
                continue;
            }
            if(e.type == SDL_MOUSEBUTTONDOWN) mousePressed = true;
            if(e.type == SDL_MOUSEBUTTONUP) mousePressed = false;
            
            if(e.type == SDL_FINGERDOWN || e.type == SDL_FINGERUP || e.type == SDL_FINGERMOTION)
            {
                // No touch events...
                continue;
            }

            for(int i = (int) menus.size() - 1; i >= 0; i--)
            {
                menus[i]->updateElements(e);
                if(menus[i]->consumeEvent)
                {
                    menus[i]->consumeEvent = false;
                    break;
                }
            }
            
            // Handle events of the window
            if(e.type == SDL_WINDOWEVENT)
            {
                if(e.window.event == SDL_WINDOWEVENT_CLOSE) running = false;
				else if (e.window.event == SDL_WINDOWEVENT_RESIZED)
				{
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
                if(e.key.keysym.sym == SDLK_ESCAPE) openMenu(new PauseMenu());
                else if(e.key.keysym.sym == GLOBAL_KEY_CONFIG[BUTTON_SHOOT])
                {
                    for(int i = 0; i < 5; i++) // Shoot n projectiles
                    {
                        ExplodingProjectile *p = new ExplodingProjectile(NORMAL, level->player->x_pos, level->player->y_pos, (float) TO_RAD(rand() % 360));
                        level->addEntity(p);
                    }
                }
                else if(e.key.keysym.sym == GLOBAL_KEY_CONFIG[BUTTON_INVENTORY]) openMenu(new Inventory(level->player));
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button == SDL_BUTTON_RIGHT)
                {
                    int xdif = (int) (e.button.x / SCALE_X) - PLAYER_OFFSET_X + level->player->xoff;
                    int ydif = (int) (e.button.y / SCALE_Y) - PLAYER_OFFSET_Y + level->player->yoff;
                    float angle = -(float) atan2(ydif, xdif);
                    
                    Projectile *p = new Projectile(level->player->x_pos, level->player->y_pos, angle);
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
        
        GLenum err = glGetError();
        if(err != GL_NO_ERROR)
        {
            printf("[ERROR] GL Error: %d\n", err);
        }

        SDL_GL_SwapWindow(window);
        
        auto end_time = clock.now();
        auto difference = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::this_thread::sleep_for(std::chrono::microseconds(16666) - difference);
    }
    
    exitGame(this);
}

void Window::reloadConfig()
{
    loader = new ConfigLoader(GET_FILE_PATH(LEVEL_PATH, "informatik.config"));
}

void exitGame(Window *window)
{
    Loader::LevelLoader loader(window->level);
    loader.saveFile(window->level->levelFile.c_str());
    
    SDL_DestroyWindow(window->window);
    SDL_Quit();
        
    exit(0);
}
