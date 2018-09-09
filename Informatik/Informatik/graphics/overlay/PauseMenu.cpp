//
//  PauseMenu.cpp
//  Informatik
//
//  Created by Aaron Hodel on 02.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "PauseMenu.hpp"

void onClick(Menu* menu, Button *button)
{
    switch(button->elementID)
    {
        case 0:
            menu->close();
            break;
        case 1:
            exit(0);
        case 2:
            updateVariant(menu->window->level, menu->window->renderer);
            break;
    }
}

PauseMenu::PauseMenu()
{
    addElement(new Button(onClick, "Continue", 0, 0, 500, 100, 0));
    addElement(new Button(onClick, "Exit", 0, 100, 500, 100, 1));
    addElement(new Button(onClick, "Update variants", 0, 400, 500, 100, 2));
}

bool PauseMenu::shouldWindowClose() { return false; }

void PauseMenu::updateElements(SDL_Event e)
{
    Menu::updateElements(e);

    if(e.type == SDL_KEYDOWN)
    {
        if(e.key.keysym.sym == SDLK_ESCAPE)
        {
            exit(0);
        }
    }
}

void PauseMenu::renderMenu(SDL_Renderer *renderer)
{
    SDL_Rect r = {0, 0, GAME_WIDTH, GAME_HEIGHT};
    COLOR(renderer, 0x55FFFFFF);
    SDL_RenderFillRect(renderer, &r);
}

void PauseMenu::drawOverlay(SDL_Renderer *renderer) {}
void PauseMenu::updateMenu(const uint8_t *keys) { if(keys[SDL_SCANCODE_SPACE]) close(); }
void PauseMenu::onOpen() {}
void PauseMenu::onClose() {}
