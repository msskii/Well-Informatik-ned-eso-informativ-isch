//
//  EventCreateMenu.cpp
//  Informatik
//
//  Created by Aaron Hodel on 24.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "EventCreateMenu.hpp"

static void buttonClick(Menu *menu, Button *button)
{
    if(button->id == 0)
    {
        menu->close();
    }
    else if(button->id == 1)
    {
        SerializedEvent evt;
        uint8_t *args = nullptr;
        menu->window->level->events[atoi(((TextBox*)menu->getElement<TextBox>(0))->currentText.c_str())] = Event(evt, args);
        menu->close();
    }
}

EventCreateMenu::EventCreateMenu()
{
    addElement(new TextBox("ID", 0, 0, 500, 100));
    addElement(new TextBox("X", 0, 100, 500, 100));
    addElement(new TextBox("Y", 0, 200, 500, 100));

    addElement(new Button(buttonClick, "Ok", 325, 400, 100, 100, 0));
    addElement(new Button(buttonClick, "Cancel", 0, 400, 250, 100, 1));
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
