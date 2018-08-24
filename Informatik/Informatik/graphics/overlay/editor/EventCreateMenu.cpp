//
//  EventCreateMenu.cpp
//  Informatik
//
//  Created by Aaron Hodel on 24.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "EventCreateMenu.hpp"

EventCreateMenu::EventCreateMenu()
{
    addElement(new TextBox("TestBox", 0, 0, 500, 125));
}

bool EventCreateMenu::shouldWindowClose() { return false; }

void EventCreateMenu::renderMenu(SDL_Renderer *renderer)
{
    COLOR(renderer, 0xFFFFFFFF);
    SDL_Rect r = {0, 0, 500, 500};
    SDL_RenderFillRect(renderer, &r);
}

void EventCreateMenu::updateMenu(const uint8_t *keys) {}
void EventCreateMenu::onOpen() {}
void EventCreateMenu::onClose() {}
