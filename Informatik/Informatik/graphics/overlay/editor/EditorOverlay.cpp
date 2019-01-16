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


void EditorClickHandler::render()
{
    if(!menu->active) return;
    
    SDL_GetMouseState(&x, &y);
    x = (int)(x / SCALE_X);
    y = (int)(y / SCALE_Y);
    
    selectedID = (int) ((x - menu->window->level->getLocalPlayer()->getOffsetX() - PLAYER_OFFSET_X) / TILE_SIZE) + (int) ((y - menu->window->level->getLocalPlayer()->getOffsetY() - PLAYER_OFFSET_Y) / TILE_SIZE) * menu->window->level->width;
}


void EditorClickHandler::processEvent(Menu *menu, SDL_Event e)
{
    if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) pressed = true;
    if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) pressed = false;
}

EditorOverlay::EditorOverlay()
{
    clickhandler = (EditorClickHandler*) addElement(new EditorClickHandler());
    
    shouldLevelBeUpdated = true;
}

bool EditorOverlay::shouldWindowClose() { return false; }

void EditorOverlay::renderMenu()
{
    if(state == EVENT)
    {
        Event *e = nullptr;
        for(int i = 0; i < (int) window->level->events.size(); i++)
        {
            Event *evt = window->level->events[i];
            int xpos = evt->event_data.event_x + window->level->getLocalPlayer()->getOffsetX() + PLAYER_OFFSET_X;
            int ypos = evt->event_data.event_y + window->level->getLocalPlayer()->getOffsetY() + PLAYER_OFFSET_Y;
            // printf("%i: xd: (%d - %d), yd: %d\n", i, xpos, clickhandler->x, ypos - clickhandler->y);
            if(xpos <= clickhandler->x && xpos + evt->event_data.event_w >= clickhandler->x && ypos <= clickhandler->y && ypos + evt->event_data.event_h >= clickhandler->y)
            {
                e = evt;
                break;
            }
        }
        if(e == nullptr) return;
        
        int xpos = e->event_data.event_x + window->level->getLocalPlayer()->getOffsetX() + PLAYER_OFFSET_X;
        int ypos = e->event_data.event_y + window->level->getLocalPlayer()->getOffsetY() + PLAYER_OFFSET_Y;
        SDL_Rect dst = {xpos, ypos, e->event_data.event_w, e->event_data.event_h};
        fillRect(0xAFFFFFF, dst);
    }
    else if(state == TILES)
    {
        int tileX = clickhandler->selectedID % window->level->width;
        int tileY = clickhandler->selectedID / window->level->width;
        
        // printf("X: %d, Y: %d\n", tileX, tileY);
        
        SDL_Rect dst = { tileX * TILE_SIZE + window->level->getLocalPlayer()->getOffsetX() + PLAYER_OFFSET_X, tileY * TILE_SIZE + window->level->getLocalPlayer()->getOffsetY() + PLAYER_OFFSET_Y, TILE_SIZE, TILE_SIZE };
        fillRect(0xAFFFFFF, dst);
    }
    else if(state == BUILDING)
    {
        for(size_t i = 0; i < window->level->buildings.size(); i++)
        {
            if(window->level->buildings[i]->isInside((float) (clickhandler->x - window->level->getLocalPlayer()->getOffsetX() - PLAYER_OFFSET_X), (float) (clickhandler->y - window->level->getLocalPlayer()->getOffsetY() - PLAYER_OFFSET_Y)))
            {
                SDL_Rect dst = { (int) (window->level->buildings[i]->data.hitboxX * TILE_SIZE) + window->level->getLocalPlayer()->getOffsetX() + PLAYER_OFFSET_X, (int) (window->level->buildings[i]->data.hitboxY * TILE_SIZE) + window->level->getLocalPlayer()->getOffsetY() + PLAYER_OFFSET_Y, (int) (window->level->buildings[i]->data.hitboxsizeX * TILE_SIZE), (int) (window->level->buildings[i]->data.hitboxsizeY * TILE_SIZE) };
                fillRect(0xAFFFFFFF, dst);
                break;
            }
        }

    }
}

void EditorOverlay::updateMenu(const uint8_t *keys)
{
    if(keys[SDL_SCANCODE_E])
    {
        // Enabled event editor
        state = EVENT;
    }
    if(keys[SDL_SCANCODE_T])
    {
        // Disable event editor
        state = TILES;
    }
    if(keys[SDL_SCANCODE_B])
    {
        state = BUILDING;
    }
    
    if(keys[SDL_SCANCODE_N])
    {
        openSubMenu(new EventCreateMenu());
    }
    
    if(clickhandler->pressed)
    {
        clickhandler->pressed = false;
        if(state == EVENT)
        {
            Event *e = nullptr;
            for(int i = 0; i < (int) window->level->events.size(); i++)
            {
                Event *evt = window->level->events[i];
                int xpos = evt->event_data.event_x + window->level->getLocalPlayer()->getOffsetX() + PLAYER_OFFSET_X;
                int ypos = evt->event_data.event_y + window->level->getLocalPlayer()->getOffsetY() + PLAYER_OFFSET_Y;
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
        else if(state == TILES)
        {
            int tileX = clickhandler->selectedID % window->level->width;
            int tileY = clickhandler->selectedID / window->level->width;
            
            int tileIndex = tileX + tileY * window->level->width;
            
            openSubMenu(new TileEditor(window->level, tileIndex));
        }
        else if(state == BUILDING)
        {
            for(size_t i = 0; i < window->level->buildings.size(); i++)
            {
                if(window->level->buildings[i]->isInside((float) (clickhandler->x - window->level->getLocalPlayer()->getOffsetX() - PLAYER_OFFSET_X), (float) (clickhandler->y - window->level->getLocalPlayer()->getOffsetY() - PLAYER_OFFSET_Y)))
                {
                    printf("Over building...\n");
                    
                    break;
                }
            }
        }
    }
}

void EditorOverlay::drawOverlay() {}
void EditorOverlay::onOpen() {}
void EditorOverlay::onClose() {}
