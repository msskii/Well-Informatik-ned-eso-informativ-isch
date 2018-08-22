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
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WIDTH, GAME_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    
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
    level->update(); // Update rest of level according to player
}

void Window::openMenu(Menu *m)
{
    menu = m;
    m->active = true;
    m->open();
}

void Window::render(SDL_Renderer *renderer)
{
    level->render(renderer); // Render level, but don't update
    if(menu != nullptr)
    {
        if(menu->shouldWindowClose() || menu->menuShouldBeClosed)
        {
            menu->onClose();
            menu = nullptr;
            INFO("Closing Menu...");
        } else menu->render(renderer, keyStates);
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
            // Handle events of the window
            if(e.type == SDL_WINDOWEVENT)
            {
                if(e.window.event == SDL_WINDOWEVENT_CLOSE) running = false;
            }
            else if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_ESCAPE) running = false;
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF); // Black
        SDL_RenderClear(renderer); // Everything black
        
        // Update & render
        if(menu == nullptr) update();
        render(renderer);
        
        SDL_RenderPresent(renderer); // Draw & limit FPS
    }
    
    LevelLoader loader(level);
    loader.saveFile("testlevel.level");
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
