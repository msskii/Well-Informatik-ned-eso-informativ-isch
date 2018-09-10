//
//  ConfigMenu.cpp
//  Informatik
//
//  Created by Aaron Hodel on 10.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "ConfigMenu.hpp"

ConfigMenu::ConfigMenu(ConfigLoader *loader)
{
    addElement(new TextBox("DefaultText", 0, 0, 500, 100, 0));
}

bool ConfigMenu::shouldWindowClose() { return false; }
void ConfigMenu::renderMenu(SDL_Renderer *renderer)
{
    COLOR(renderer, 0xFFFFFFFF);
    SDL_RenderClear(renderer);
}
void ConfigMenu::drawOverlay(SDL_Renderer *renderer) {}
void ConfigMenu::updateMenu(const uint8_t *keys) {}
void ConfigMenu::onOpen() {}
void ConfigMenu::onClose() {}
