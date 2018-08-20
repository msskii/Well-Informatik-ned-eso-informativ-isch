//
//  Window.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Window.hpp"

Window::Window()
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
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF); // Black
        SDL_RenderClear(renderer); // Everything black
        
        // Put rendering here
        
        SDL_RenderPresent(renderer); // Draw & limit FPS
    }
}
