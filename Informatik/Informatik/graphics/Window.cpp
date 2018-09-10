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
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER); // Add audio subsystem?
    if(TTF_Init() == -1)
    {
        printf("TTF_Init error: %s\n", TTF_GetError());
        exit(2);
    }
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    
    // Load config
    ConfigLoader loader(GET_FILE_PATH(LEVEL_PATH, "informatik.config"));
    key_inventory = loader.getInt("button.inventory");
    key_shoot = loader.getInt("button.shoot");

    font = TTF_OpenFont(GET_FILE_PATH(FONT_PATH, "Raleway-Regular.ttf"), 64); // Window opened = font initialized
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "2");
    
    if(!font)
    {
        ERROR("Couldn't open font file...");
        printf("%s\n", TTF_GetError());
        exit(0);
    }
    
#ifdef FULLSCREEN_ENABLED
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
#else
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
#endif
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Alpha color --> Invisible
    
    // Set up level
    level = Loader::loadLevel(GET_FILE_PATH(LEVEL_PATH, "testlevel.level"), 50, 50, renderer);
    
    // Set up scaling
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SCALE_X = (float) w / (float) GAME_WIDTH;
    SCALE_Y = (float) h / (float) GAME_HEIGHT;
    SDL_RenderSetScale(renderer, SCALE_X, SCALE_Y);
    
    // Set up keystates & level
    keyStates = SDL_GetKeyboardState(NULL);
    level->window = this;
    
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
    
    Slime *slime = new Slime(10 * TILE_SIZE, 5 * TILE_SIZE);
    level->addEntity(slime);
    
    Projectile *projectile = new Projectile(0, 0, PI * 15.0 / 8.0);
    level->addEntity(projectile);
    
    
    for(int i = 0; i < 22; i++)
    {
        level->addEntity(new EntityItem(5, i, new Item("test", renderer)));
        level->addEntity(new EntityItem(3, i, new Item("test2", renderer)));
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
    if(keyStates[SDL_SCANCODE_UP]) y -= SPEED;
    if(keyStates[SDL_SCANCODE_DOWN]) y += SPEED;
    if(keyStates[SDL_SCANCODE_RIGHT]) x += SPEED;
    if(keyStates[SDL_SCANCODE_LEFT]) x -= SPEED;
    
    level->player->updateMovement(x, y); // Update player movement
    level->player->actionPressed = keyStates[SDL_SCANCODE_RETURN];
    
    level->update(); // Update rest of level according to player
}

void Window::openMenu(Menu *m)
{
    m->active = true;
    menus.push_back(m);
    m->open(this);
}

void Window::render(SDL_Renderer *renderer)
{
    level->render(renderer); // Render level, but don't update
    
    for(int i = 0; i < (int) menus.size(); i++)
    {
        if(menus[i]->shouldWindowClose() || menus[i]->menuShouldBeClosed)
        {
            if(i != 0) menus[menus.size() - 1]->active = true;
            menus[i]->onClose();
            menus.erase(menus.begin() + i);
        } else menus[i]->render(renderer, keyStates);
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

            for(int i = (int) menus.size() - 1; i >= 0; i--) menus[i]->updateElements(e);
            
            // Handle events of the window
            if(e.type == SDL_WINDOWEVENT)
            {
                if(e.window.event == SDL_WINDOWEVENT_CLOSE) running = false;
				if (e.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					int w, h;
					SDL_GetWindowSize(window, &w, &h);
					SCALE_X = (float)w / (float)GAME_WIDTH;
					SCALE_Y = (float)h / (float)GAME_HEIGHT;
					SDL_RenderSetScale(renderer, SCALE_X, SCALE_Y);
				}
            }
            
            // Player & Level control:
            if(!toUpdate) continue; // We're paused...
            
            if(e.type == SDL_KEYDOWN)
            {                
                if(e.key.keysym.sym == SDLK_ESCAPE) openMenu(new PauseMenu());
                else if(e.key.keysym.sym == key_shoot)
                {
                    for(int i = 0; i < 5; i++) // Shoot n projectiles
                    {
                        ExplodingProjectile *p = new ExplodingProjectile(NORMAL, level->player->x_pos, level->player->y_pos, TO_RAD(rand() % 360));
                        level->addEntity(p);
                    }
                }
                else if(e.key.keysym.sym == key_inventory) openMenu(new Inventory(level->player));
            }
            else if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                if(e.button.button == SDL_BUTTON_RIGHT)
                {
                    int xdif = (int) (e.button.x / SCALE_X) - PLAYER_OFFSET_X + level->player->xoff;
                    int ydif = (int) (e.button.y / SCALE_Y) - PLAYER_OFFSET_Y + level->player->yoff;
                    float angle = -atan2(ydif, xdif);
                    
                    Projectile *p = new Projectile(level->player->x_pos, level->player->y_pos, angle);
                    level->addEntity(p);
                }
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF); // Black
        SDL_RenderClear(renderer); // Everything black
        
        // Update & render
        toUpdate = true;
        for(int i = 0; i < (int) menus.size(); i++)
        {
            // menus[i]->updateElements(e); // What was I doing?
            if(!menus[i]->shouldLevelBeUpdated) toUpdate = false;
        }
        if(toUpdate) update();
        render(renderer);
        
        auto end_time = clock.now();
        auto difference = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::this_thread::sleep_for(std::chrono::microseconds(16666) - difference);
        
        SDL_RenderPresent(renderer); // Draw & limit FPS when opened
    }
    
    Loader::LevelLoader loader(level);
    loader.saveFile(GET_FILE_PATH(LEVEL_PATH, "testlevel.level"));
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
