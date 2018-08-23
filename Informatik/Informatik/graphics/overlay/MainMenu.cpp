//
//  MainMenu.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "MainMenu.hpp"

#define START_GAME 1
#define UNDEF_1 2
#define UNDEF_2 3

static void onButtonPress(Menu *menu, int buttonID)
{
    switch (buttonID) {
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
    
}

MainMenu::MainMenu()
{
    addElement(new Button(onButtonPress, "Start Game", 100, 200, 400, 100, START_GAME));
    addElement(new Button(onButtonPress, "Undef 1", 100, 300, 400, 100, UNDEF_1));
    addElement(new Button(onButtonPress, "Undef 2", 100, 400, 400, 100, UNDEF_2));
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
