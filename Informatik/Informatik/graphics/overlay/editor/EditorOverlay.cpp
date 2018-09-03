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
    
    SDL_GetMouseState(&x, &y);
    x = (int)(x / SCALE_X);
    y = (int)(y / SCALE_Y);
    
    selectedID = (int) ((x - menu->window->level->player->getOffsetX() - PLAYER_OFFSET_X) / TILE_SIZE) + (int) ((y - menu->window->level->player->getOffsetY() - PLAYER_OFFSET_Y) / TILE_SIZE) * menu->window->level->width;
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
    if(eventEditorEnabled)
    {
        Event *e = nullptr;
        for(int i = 0; i < (int) window->level->events.size(); i++)
        {
            Event *evt = window->level->events[i];
            int xpos = evt->event_data.event_x - window->level->player->getOffsetX() - PLAYER_OFFSET_X;
            int ypos = evt->event_data.event_y - window->level->player->getOffsetY() - PLAYER_OFFSET_Y;
            // printf("%i: xd: (%d - %d), yd: %d\n", i, xpos, clickhandler->x, ypos - clickhandler->y);
            if(xpos <= clickhandler->x && xpos + evt->event_data.event_w >= clickhandler->x && ypos <= clickhandler->y && ypos + evt->event_data.event_h >= clickhandler->y)
            {
                e = evt;
                break;
            }
        }
        if(e == nullptr) return;
        
        COLOR(renderer, 0xAFFFFFFF);
        int xpos = e->event_data.event_x - window->level->player->getOffsetX() - PLAYER_OFFSET_X;
        int ypos = e->event_data.event_y - window->level->player->getOffsetY() - PLAYER_OFFSET_Y;
        SDL_Rect dst = {xpos, ypos, e->event_data.event_w, e->event_data.event_h};
        SDL_RenderFillRect(renderer, &dst);
    }
    else
    {
        COLOR(renderer, 0xAFFFFFFF);
        int tileX = clickhandler->selectedID % window->level->width;
        int tileY = clickhandler->selectedID / window->level->width;
        
        // printf("X: %d, Y: %d\n", tileX, tileY);
        
        SDL_Rect dst = { tileX * TILE_SIZE + window->level->player->getOffsetX() + PLAYER_OFFSET_X, tileY * TILE_SIZE + window->level->player->getOffsetY() + PLAYER_OFFSET_Y, TILE_SIZE, TILE_SIZE };
        SDL_RenderFillRect(renderer, &dst);

    }
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
    
    if(keys[SDL_SCANCODE_N])
    {
        openSubMenu(new EventCreateMenu());
    }
    
    if(clickhandler->pressed)
    {
        clickhandler->pressed = false;
        if(eventEditorEnabled)
        {
            Event *e = nullptr;
            for(int i = 0; i < (int) window->level->events.size(); i++)
            {
                Event *evt = window->level->events[i];
                int xpos = evt->event_data.event_x - window->level->player->getOffsetX() - PLAYER_OFFSET_X;
                int ypos = evt->event_data.event_y - window->level->player->getOffsetY() - PLAYER_OFFSET_Y;
                if(xpos <= clickhandler->x && xpos + evt->event_data.event_w >= clickhandler->x && ypos <= clickhandler->y && ypos + evt->event_data.event_h >= clickhandler->y)
                {
                    e = evt;
                    break;
                }
            }
            if(e == nullptr)
            {
                // Create new event at location of mouse
                EventData data;
                data.event_x = clickhandler->x;
                data.event_y = clickhandler->y;
                e = new Event(data, new uint8_t[1]{});
            }
            openSubMenu(new EventCreateMenu(e));
        }
        else
        {
            int tileX = clickhandler->selectedID % window->level->width;
            int tileY = clickhandler->selectedID / window->level->width;
            
            int tileIndex = tileX + tileY * window->level->width;
            
            openSubMenu(new TileEditor(window->level, tileIndex));
        }
    }
}

void EditorOverlay::onOpen() {}
void EditorOverlay::onClose() {}
