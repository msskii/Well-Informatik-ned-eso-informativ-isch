//
//  MainMenu.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "MainMenu.hpp"
#include "config.h"

#define START_GAME 1
#define UNDEF_1 2
#define UNDEF_2 3

static void onButtonPress(Menu *menu, Button *button)
{
<<<<<<< HEAD
    printf("Button pressed\n");
    menu->close(); // Close the menu that is currently open (Main Menu)
    
    switch (buttonID)
    {
        
        
        
    }
    
    
=======
    switch (button->elementID) {
        case START_GAME:
            menu->close(); // Close the menu that is currently open (Main Menu)
            break;
        case UNDEF_1:
            break;
        case UNDEF_2:
            break;
        default:
            break;
    }
    
>>>>>>> 12453a881de2c1c2548390e0eeaf8cdf150f3534
}



MainMenu::MainMenu()
{
<<<<<<< HEAD
    addElement(new Button(onButtonPress, "Start Game", (GAME_WIDTH / 2 -100), (GAME_HEIGHT/2 + -100), 200, 50));
    addElement(new Button(onButtonPress, "Level Editor", GAME_WIDTH / 2 -100 , GAME_HEIGHT/2 -25, 200,50));
    addElement(new Button(onButtonPress, "Quit", (GAME_WIDTH / 2 -100), (GAME_HEIGHT/2 + 50), 200, 50));
=======
    addElement(new Button(onButtonPress, "Start Game", 100, 200, 400, 100, START_GAME));
    addElement(new Button(onButtonPress, "Undef 1", 100, 300, 400, 100, UNDEF_1));
    addElement(new Button(onButtonPress, "Undef 2", 100, 400, 400, 100, UNDEF_2));
>>>>>>> 12453a881de2c1c2548390e0eeaf8cdf150f3534
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
