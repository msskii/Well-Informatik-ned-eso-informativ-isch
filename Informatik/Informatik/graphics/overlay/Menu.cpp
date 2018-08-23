//
//  Menu.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Menu.hpp"

void Menu::render(SDL_Renderer *renderer, const uint8_t *keys)
{
    if(active)
    {
        // Render menus
        renderMenu(renderer);
        updateMenu(keys);
        
        for(int i = 0; i < elements.size(); i++) elements[i]->render(renderer);
    }
    else if(under != nullptr)
    {
        under->render(renderer, keys); // Forward rendering process to submenu
    }
    else
    {
        ERROR("Menu is not active and has no parent! Making this menu active again");
        active = true;
    }
}

void Menu::updateElements(SDL_Event e)
{
    if(under == nullptr) for(int i = 0; i < elements.size(); i++) elements[i]->processEvent(this, e);
    else under->updateElements(e);
}

Element *Menu::addElement(Element *e)
{
    elements.push_back(e);
    return e;
}

void Menu::open()
{
    active = true;
    menuShouldBeClosed = false; // Just to make sure, if same menu is reopened
    onOpen();
}

void Menu::close()
{
    active = false;
    under = nullptr;
    menuShouldBeClosed = true;
    // On close will be called from the window
}
