//
//  DebugOverlay.cpp
//  Informatik
//
//  Created by Aaron Hodel on 24.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "DebugOverlay.hpp"

static const char* updateDebugText(Menu *menu, DebugText *text)
{
    if(text->y == 000) snprintf(text->buffer, text->maxLength + 1, text->format, menu->window->level->player->_x);
    if(text->y == 100) snprintf(text->buffer, text->maxLength + 1, text->format, menu->window->level->player->_y);
    if(text->y == 200) snprintf(text->buffer, text->maxLength + 1, text->format, menu->window->level->player->_z);

    return text->buffer;
}

DebugOverlay::DebugOverlay(Level *l) : level(l)
{
    shouldLevelBeUpdated = true;
    
    addElement(new DebugText("Player X = %.0f", 40, updateDebugText, GAME_WIDTH - 500, 0, 500, 100));
    addElement(new DebugText("Player Y = %.0f", 40, updateDebugText, GAME_WIDTH - 500, 100, 500, 100));
    addElement(new DebugText("Player Z = %d", 40, updateDebugText, GAME_WIDTH - 500, 200, 500, 100));
}

bool DebugOverlay::shouldWindowClose() {return false;}

void DebugOverlay::renderMenu(SDL_Renderer *renderer)
{
    COLOR(renderer, 0x77FFFFFF);
    SDL_Rect r = {GAME_WIDTH - 500, 0, 500, GAME_HEIGHT};
    SDL_RenderFillRect(renderer, &r);
}

void DebugOverlay::updateMenu(const uint8_t *keys)
{
    
}

void DebugOverlay::onOpen(){}
void DebugOverlay::onClose(){}
