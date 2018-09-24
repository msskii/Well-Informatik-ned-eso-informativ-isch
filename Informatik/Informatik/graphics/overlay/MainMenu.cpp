//
//  MainMenu.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "MainMenu.hpp"
#include "../../config.h"

#include "../../multiplayer/ServerSelector.hpp"

enum MenuOptions
{
    START_GAME,
    START_LEVELEDITOR,
    START_OPTIONS,
    QUIT_GAME,
    START_SERVER, // Testing only
	CONNECT_TO_SERVER
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
        case START_OPTIONS:
            //menu->window->openMenu(new ConfigMenu(menu->window->loader));
            menu->openSubMenu(new ConfigMenu(menu->window->loader));
            break;
        case QUIT_GAME:
            exitGame(menu->window);
            break;
        case START_SERVER:
        {
            Multiplayer::Server s = Multiplayer::Server(menu->window); // Start a server
        }
            menu->close();
            break;
		case CONNECT_TO_SERVER:
			menu->openSubMenu(new Multiplayer::ServerSelector(menu));
            menu->window->level->remoteLevel = true; // Connected to a server
			break;
        default:
            break;
    }

}

MainMenu::MainMenu()
{
    addElement(new Button(onButtonPress, "Start Game", 100, 200, 400, 100, START_GAME));
    addElement(new Button(onButtonPress, "Level Editor", 100, 300, 400, 100, START_LEVELEDITOR));
    addElement(new Button(onButtonPress, "Options", 100, 400, 400, 100, START_OPTIONS));
    addElement(new Button(onButtonPress, "Quit", 100, 500, 400, 100, QUIT_GAME));
    
    addElement(new Button(onButtonPress, "Start Server", 100, 700, 400, 100, START_SERVER));
	addElement(new Button(onButtonPress, "Connect", 100, 800, 400, 100, CONNECT_TO_SERVER));
}

bool MainMenu::shouldWindowClose()
{
    return gameStart;
}

void MainMenu::renderMenu()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    fillRect(0xFFFF00FF, {0, 0, 10, 10});
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
