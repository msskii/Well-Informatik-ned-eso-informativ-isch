//
//  Window.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Window.hpp"

Window::Window() : level(loadLevel("testlevel.level", 50, 50)) // Load from file, or if not found w = 50 & h = 50
{
    SDL_Init(SDL_INIT_VIDEO); // Add audio subsystem?
    
    if(TTF_Init() == -1) {
        printf("TTF_Init error: %s\n", TTF_GetError());
        exit(2);
    }

    // Init image loading (JPG & PNG for now)
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    //font = TTF_OpenFont("Ormont_Light.ttf", 16); // Window opened = font initialized
    font = TTF_OpenFont("Raleway-Regular.ttf", 50); // Window opened = font initialized

    if(!font)
    {
        ERROR("Couldn't open font file...");
        printf("%s\n", TTF_GetError());
        exit(0);
    }
    
    TTF_SetFontOutline(font, 0);
    
#ifdef FULLSCREEN_ENABLED
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
#else
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
#endif
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SCALE_X = (float) w / (float) GAME_WIDTH;
    SCALE_Y = (float) h / (float) GAME_HEIGHT;
    SDL_RenderSetScale(renderer, SCALE_X, SCALE_Y);
    
#ifdef DEBUG_OVERLAY
    openMenu(new DebugOverlay(level));
#endif
    
    openMenu(new MainMenu());
    
    keyStates = SDL_GetKeyboardState(NULL);
}

void Window::update()
{
    // Put update stuff here
    float x = 0, y = 0;
    if(keyStates[SDL_SCANCODE_UP])
    {
        y -= SPEED;
    }
    if(keyStates[SDL_SCANCODE_DOWN])
    {
        y += SPEED;
    }
    if(keyStates[SDL_SCANCODE_RIGHT])
    {
        x += SPEED;
    }
    if(keyStates[SDL_SCANCODE_LEFT])
    {
        x -= SPEED;
    }
    
    level->player->updateMovement(x, y); // Update player movement
    level->player->actionPressed = keyStates[SDL_SCANCODE_RETURN];
    
    level->update(); // Update rest of level according to player
}

void Window::openMenu(Menu *m)
{
    menus.push_back(m);
    for(int i = 0; i < (int) menus.size(); i++) menus[i]->active = false; // Set the menus to not be active, that are beneath
    m->active = true;
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
            INFO("Closing Menu...");
        } else menus[i]->render(renderer, keyStates);
    }
}

void Window::runGameLoop()
{
    running = true;
    SDL_Event e;
    
    while(running)
    {
        while(SDL_PollEvent(&e))
        {
            for(int i = 0; i < (int) menus.size(); i++) menus[i]->updateElements(e);
            
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
            else if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_ESCAPE) running = false;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF); // Black
        SDL_RenderClear(renderer); // Everything black
        
        // Update & render
        bool toUpdate = true;
        for(int i = 0; i < (int) menus.size(); i++)
        {
            menus[i]->updateElements(e);
            if(!menus[i]->shouldLevelBeUpdated) toUpdate = false;
        }
        if(toUpdate) update();
        render(renderer);
                
        SDL_RenderPresent(renderer); // Draw & limit FPS
    }
    
    LevelLoader loader(level);
    loader.saveFile("testlevel.level");
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
