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
    
}


void EditorClickHandler::processEvent(Menu *menu, SDL_Event e)
{
    if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        printf("Mouse button down\n");
    }
}

EditorOverlay::EditorOverlay()
{
    addElement(new EditorClickHandler());
}

bool EditorOverlay::shouldWindowClose() { return false; }
void EditorOverlay::renderMenu(SDL_Renderer *renderer) {}
void EditorOverlay::updateMenu(const uint8_t *keys) {}
void EditorOverlay::onOpen() {}
void EditorOverlay::onClose() {}
