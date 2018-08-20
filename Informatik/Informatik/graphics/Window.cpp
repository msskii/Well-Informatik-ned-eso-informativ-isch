//
//  Window.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Window.hpp"

Window::Window() : level(new Level(50, 50))
{
    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WIDTH, GAME_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
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
        
        // Put update stuff here
        const uint8_t *keys = SDL_GetKeyboardState(NULL);
        
        float x = 0, y = 0;
        if(keys[SDL_SCANCODE_UP])
        {
            y -= SPEED;
        }
        if(keys[SDL_SCANCODE_DOWN])
        {
            y += SPEED;
        }
        if(keys[SDL_SCANCODE_RIGHT])
        {
            x += SPEED;
        }
        if(keys[SDL_SCANCODE_LEFT])
        {
            x -= SPEED;
        }
        level->player->updateMovement(x, y);
        
        // Put rendering here
        level->render(renderer);
        
        SDL_RenderPresent(renderer); // Draw & limit FPS
    }
}
