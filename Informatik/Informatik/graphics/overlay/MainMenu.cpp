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
#define START_LEVEREDITOR 2
#define QUIT_GAME 3

static void onButtonPress(Menu *menu, Button *button)
{

    switch (button->elementID) {
        case START_GAME:
            menu->close(); // Close the menu that is currently open (Main Menu)
            break;
        case START_LEVEREDITOR:
            menu->close();
            menu->window->openMenu(new EditorOverlay());
            break;
        case QUIT_GAME:
            exit(0);
            break;
        default:
            break;
    }

}

MainMenu::MainMenu()
{
    addElement(new Button(onButtonPress, "Start Game", 100, 200, 400, 100, START_GAME));
    addElement(new Button(onButtonPress, "Level Editor", 100, 300, 400, 100, START_LEVEREDITOR));
    addElement(new Button(onButtonPress, "Quit", 100, 400, 400, 100, QUIT_GAME));
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
