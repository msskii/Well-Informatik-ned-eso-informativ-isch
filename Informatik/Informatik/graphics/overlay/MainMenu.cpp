//
//  MainMenu.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "MainMenu.hpp"

static void onButtonPress(Menu *menu, int buttonID)
{
    printf("Button pressed\n");
    menu->close(); // Close the menu that is currently open (Main Menu)
}

MainMenu::MainMenu()
{
    addElement(new Button(onButtonPress, 0, 0, 100, 25));
}

bool MainMenu::shouldWindowClose()
{
    return gameStart;
}

void MainMenu::renderMenu(SDL_Renderer *renderer)
{
    
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
