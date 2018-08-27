//
//  MainMenu.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "MainMenu.hpp"
#include "config.h"

static void onButtonPress(Menu *menu, int buttonID)
{
    printf("Button pressed\n");
    menu->close(); // Close the menu that is currently open (Main Menu)
    
    switch (buttonID)
    {
        
        
        
    }
    
    
}



MainMenu::MainMenu()
{
    addElement(new Button(onButtonPress, "Start Game", (GAME_WIDTH / 2 -100), (GAME_HEIGHT/2 + -100), 200, 50));
    addElement(new Button(onButtonPress, "Level Editor", GAME_WIDTH / 2 -100 , GAME_HEIGHT/2 -25, 200,50));
    addElement(new Button(onButtonPress, "Quit", (GAME_WIDTH / 2 -100), (GAME_HEIGHT/2 + 50), 200, 50));
}

bool MainMenu::shouldWindowClose()
{
    return gameStart;
}

void MainMenu::renderMenu(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);
}

void MainMenu::updateMenu(const uint8_t *keys)
{
    if(keys[SDL_SCANCODE_SPACE]) gameStart = true;
}

void MainMenu::onOpen()
{
    
}

void MainMenu::onClose()
{
    
}
