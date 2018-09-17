//
//  LightOverlay.cpp
//  Informatik
//
//  Created by Aaron Hodel on 17.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "LightOverlay.hpp"

LightOverlay::LightOverlay(SDL_Renderer *renderer)
{    
    shouldLevelBeUpdated = true;
}

bool LightOverlay::shouldWindowClose() { return false; }

void LightOverlay::renderMenu(SDL_Renderer *renderer)
{
    
}

void LightOverlay::drawOverlay(SDL_Renderer *renderer) {}

void LightOverlay::updateMenu(const uint8_t *keys)
{
    
}

void LightOverlay::onOpen() {}
void LightOverlay::onClose() {}
