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

void Menu::render(const uint8_t *keys)
{
    if(background_surface != nullptr && background_texture.id == 0) background_texture = getTexture(background_surface);
    if(background_texture.id != 0) renderWithoutShading(background_texture, {}, {0, 0, GAME_WIDTH, GAME_HEIGHT});
    
    renderMenu(); // Render menu (background stuff)
    for(int i = 0; i < (int) elements.size(); i++) elements[i]->render(); // Render elements of the menu

    if(active)
    {
        updateMenu(keys); // Update only if active
    }
    else if(under != nullptr)
    {
        under->render(keys); // Forward rendering process to submenu
		if (under == nullptr) return; // Closed in render function

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
    
    drawOverlay(); // The the foreground
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

Element *Menu::removeElement(Element *e)
{
    for(int i = 0; i < (int) elements.size(); i++) if(elements[i] == e) elements.erase(elements.begin() + i);
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
