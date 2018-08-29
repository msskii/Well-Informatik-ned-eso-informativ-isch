//
//  Menu.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Menu.hpp"

Menu::~Menu()
{
    
}

void Menu::render(SDL_Renderer *renderer, const uint8_t *keys)
{
    renderMenu(renderer);
    for(int i = 0; i < (int)elements.size(); i++) elements[i]->render(renderer);

    if(active)
    {
        updateMenu(keys); // Update only if active
    }
    else if(under != nullptr)
    {
        under->render(renderer, keys); // Forward rendering process to submenu
        if(under->shouldWindowClose() || under->menuShouldBeClosed)
        {
			active = true;
			under->onClose();
            under = nullptr;
            // delete under;
        }
    }
    else
    {
        ERROR("Menu is not active and has no parent! Making this menu active again");
        active = true;
    }
}

void Menu::updateElements(SDL_Event e)
{
    if(under == nullptr)
    {
        for(int i = (int) elements.size() - 1; i >= 0; i--) // Go back...
        {
            elements[i]->processEvent(this, e);
            if(elements[i]->consumeEvent)
            {
                elements[i]->consumeEvent = false;
                return; // Event consumed....
            }
        }
    }
    else under->updateElements(e);
}

Element *Menu::addElement(Element *e)
{
    elements.push_back(e);
    e->addToMenu(this);
    return e;
}

void Menu::open(Window *window)
{
    active = true;
    this->window = window;
    menuShouldBeClosed = false; // Just to make sure, if same menu is reopened
    onOpen();
}

void Menu::openSubMenu(Menu *menu)
{
    active = false;
    under = menu;
    menu->open(window);
}

void Menu::close()
{
    active = false;
    under = nullptr;
    menuShouldBeClosed = true;
    // On close will be called from the window
}
