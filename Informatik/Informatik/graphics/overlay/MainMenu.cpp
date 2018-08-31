//
//  MainMenu.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "MainMenu.hpp"
#include "../../config.h"

enum MenuOptions
{
    START_GAME,
    START_LEVELEDITOR, // Fixed spelling mistake
    QUIT_GAME,
    
    START_SERVER // Testing only
};

static void onButtonPress(Menu *menu, Button *button)
{

    switch (button->elementID) {
        case START_GAME:
            menu->close(); // Close the menu that is currently open (Main Menu)
            break;
        case START_LEVELEDITOR:
            menu->close();
            menu->window->openMenu(new EditorOverlay());
            break;
        case QUIT_GAME:
            exit(0);
            break;
        case START_SERVER:
        {
            Multiplayer::Server s; // Start a server
        }
            menu->close();
            break;
        default:
            break;
    }

}

MainMenu::MainMenu()
{
    addElement(new Button(onButtonPress, "Start Game", 100, 200, 400, 100, START_GAME));
    addElement(new Button(onButtonPress, "Level Editor", 100, 300, 400, 100, START_LEVELEDITOR));
    addElement(new Button(onButtonPress, "Quit", 100, 400, 400, 100, QUIT_GAME));
    
    addElement(new Button(onButtonPress, "Start Server", 100, 700, 400, 100, START_SERVER));
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
