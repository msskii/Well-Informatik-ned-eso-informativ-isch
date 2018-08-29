//
//  EditorOverlay.cpp
//  Informatik
//
//  Created by Aaron Hodel on 29.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "EditorOverlay.hpp"

EditorClickHandler::EditorClickHandler()
{
    
}


void EditorClickHandler::render(SDL_Renderer *renderer)
{
    if(!menu->active) return;
    
    int x, y;
    SDL_GetMouseState(&x, &y);
    selected = (int) ((x / SCALE_X) / TILE_SIZE) + (int) ((y / SCALE_Y) / TILE_SIZE) * menu->window->level->width;
}


void EditorClickHandler::processEvent(Menu *menu, SDL_Event e)
{
    if(e.type == SDL_MOUSEBUTTONDOWN) pressed = true;
    if(e.type == SDL_MOUSEBUTTONUP) pressed = false;
}

EditorOverlay::EditorOverlay()
{
    clickhandler = (EditorClickHandler*) addElement(new EditorClickHandler());
    
    shouldLevelBeUpdated = true;
}

bool EditorOverlay::shouldWindowClose() { return false; }

void EditorOverlay::renderMenu(SDL_Renderer *renderer)
{
    COLOR(renderer, 0xAFFFFFFF);
    SDL_Rect dst = { (int)(clickhandler->selected % window->level->width) * TILE_SIZE + (window->level->player->getOffsetX() % TILE_SIZE) + TILE_SIZE / 2, (int)(clickhandler->selected / window->level->width) * TILE_SIZE + (window->level->player->getOffsetY() % TILE_SIZE) + TILE_SIZE, TILE_SIZE, TILE_SIZE };
    SDL_RenderFillRect(renderer, &dst);
}

void EditorOverlay::updateMenu(const uint8_t *keys)
{
    if(keys[SDL_SCANCODE_E])
    {
        // Enabled event editor
        eventEditorEnabled = true;
    }
    if(keys[SDL_SCANCODE_D])
    {
        // Disable event editor
        eventEditorEnabled = false;
    }
    
    if(clickhandler->pressed)
    {
        int tileIndex = clickhandler->selected - ((PLAYER_OFFSET_X + window->level->player->getOffsetX()) / TILE_SIZE) - ((PLAYER_OFFSET_Y + window->level->player->getOffsetY()) / TILE_SIZE) * (window->level->width);
        clickhandler->pressed = false;
        
        openSubMenu(new TileEditor(window->level, tileIndex));
        printf("Tileindex: %d\n", tileIndex);
    }
}

void EditorOverlay::onOpen() {}
void EditorOverlay::onClose() {}
