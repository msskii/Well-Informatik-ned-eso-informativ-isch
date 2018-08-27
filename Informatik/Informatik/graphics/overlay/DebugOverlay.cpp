//
//  DebugOverlay.cpp
//  Informatik
//
//  Created by Aaron Hodel on 24.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "DebugOverlay.hpp"

static void buttonClick(Menu *menu, Button *button)
{
	if (button->elementID == 0) menu->openSubMenu(new EventCreateMenu());
	if (button->elementID == 1) menu->openSubMenu(new EventCreateMenu(&menu->window->level->events[((DebugOverlay*)menu)->eventIdCounter]));
}

static const char* updateDebugText(Menu *menu, DebugText *text)
{
    DebugOverlay *m = (DebugOverlay*) menu;
    
    if(text->y == 000) snprintf(text->buffer, text->maxLength + 1, text->format, menu->window->level->player->realPosX);
    else if(text->y == 100) snprintf(text->buffer, text->maxLength + 1, text->format, menu->window->level->player->realPosY);
    else if(text->y == 200) snprintf(text->buffer, text->maxLength + 1, text->format, menu->window->level->player->_z);
    else if(text->y == 300) snprintf(text->buffer, text->maxLength + 1, text->format, m->eventIdCounter);
    else if(text->y == 400) snprintf(text->buffer, text->maxLength + 1, text->format, menu->window->level->events[m->eventIdCounter].toStore.event_action);

    return text->buffer;
}

DebugOverlay::DebugOverlay(Level *l) : level(l)
{
    shouldLevelBeUpdated = true;
    
    addElement(new DebugText("Player X = %.0f", 40, updateDebugText, GAME_WIDTH - 500, 0, 500, 100, 0));
    addElement(new DebugText("Player Y = %.0f", 40, updateDebugText, GAME_WIDTH - 500, 100, 500, 100, 1));
    addElement(new DebugText("Player Z = %d", 40, updateDebugText, GAME_WIDTH - 500, 200, 500, 100, 2));
    
    addElement(new DebugText("Event ID = %d", 40, updateDebugText, GAME_WIDTH - 500, 300, 500, 100, 3));
    addElement(new DebugText("Event Action = %d", 40, updateDebugText, GAME_WIDTH - 500, 400, 500, 100, 4));
    
    addElement(new Button(buttonClick, "Add Event", GAME_WIDTH - 500, 500, 500, 100, 0));
	addElement(new Button(buttonClick, "Edit Event", GAME_WIDTH - 500, 600, 500, 100, 1));
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
    if(keys[SDL_SCANCODE_K])
    {
        if(!inc) ++eventIdCounter;
        inc = true;
    } else inc = false;
    
    if(keys[SDL_SCANCODE_J])
    {
        if(!dec) --eventIdCounter;
        dec = true;
    } else dec = false;
    
    if(eventIdCounter < 0) eventIdCounter = 0;
    if(eventIdCounter >= (int)level->events.size()) eventIdCounter = (int) level->events.size() - 1;
}

void DebugOverlay::onOpen(){}
void DebugOverlay::onClose(){}
