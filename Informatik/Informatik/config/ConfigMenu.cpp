//
//  ConfigMenu.cpp
//  Informatik
//
//  Created by Aaron Hodel on 10.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "ConfigMenu.hpp"

void buttonHandler(Menu *menu, Button* button)
{
    if(button->elementID == 1)
    {
        menu->close();
        return;
    }
    
    ConfigMenu *m = (ConfigMenu*) menu;
    
    for(int i = 0; i < m->keys.size(); i++) m->loader->set(m->keys[i]->text, m->values[i]->currentText.c_str());
    m->loader->save();
    m->window->reloadConfig();
    menu->close();
}

ConfigMenu::ConfigMenu(ConfigLoader *loader)
{
    this->loader = loader;
    
    for(auto it = loader->values.begin(); it != loader->values.end(); it++)
    {
        keys.push_back((Text*) addElement(new Text(it->first.c_str(), 0, y * 100, 400, 100)));
        TextBox* tb = (TextBox*) addElement(new TextBox(it->second.c_str(), 500, y * 100, GAME_WIDTH - 500, 100, 0));
        tb->defaultText = false;
        values.push_back(tb);
        ++y;
    }
    
    addElement(new Button(buttonHandler, "Save", 0, GAME_HEIGHT - 100, 500, 100, 0));
    addElement(new Button(buttonHandler, "Cancel", 500, GAME_HEIGHT - 100, 500, 100, 1));
}

bool ConfigMenu::shouldWindowClose() { return false; }

void ConfigMenu::renderMenu(SDL_Renderer *renderer)
{
    COLOR(renderer, 0xFFFFFFFF);
    SDL_RenderClear(renderer);
}

void ConfigMenu::drawOverlay(SDL_Renderer *renderer) {}

void ConfigMenu::updateMenu(const uint8_t *keys)
{
    for(int i = 0; i < (int) this->keys.size(); i++)
    {
        this->keys[i]->y = i * 100 - scrollAmount;
        values[i]->y = i * 100 - scrollAmount;
    }
    
    if(keys[SDL_SCANCODE_DOWN])
    {
        scrollAmount += SCROLL_SPEED;
    }
    else if(keys[SDL_SCANCODE_UP])
    {
        scrollAmount -= SCROLL_SPEED;
    }
}

void ConfigMenu::onOpen() {}
void ConfigMenu::onClose() {}
