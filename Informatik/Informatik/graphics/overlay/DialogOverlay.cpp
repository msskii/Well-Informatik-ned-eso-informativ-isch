//
//  DialogOverlay.cpp
//  Informatik
//
//  Created by Aaron Hodel on 27.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "DialogOverlay.hpp"

DialogOverlay::DialogOverlay(const char *t) : text(std::string(t))
{
    shouldLevelBeUpdated = true;
}

bool DialogOverlay::shouldWindowClose()
{
    return dialogOver;
}

void DialogOverlay::renderMenu()
{
    SDL_Rect dst = {0, GAME_HEIGHT - 400, GAME_WIDTH, 400};
    fillRect(0xFFFFFFFF, dst);
    
    int fnl = (int) text.find("\n");
    std::string line1 = text.substr(0, fnl);
    std::string rest = text.substr(fnl + 1);
    int snl = (int) rest.find("\n");
    std::string line2 = rest.substr(0, snl);
    
    drawTextAspect(line1.c_str(), 0xFF000000, {0, GAME_HEIGHT - 400, GAME_WIDTH, 200}, textCache1, false);
    if(fnl > 0) drawTextAspect(line2.c_str(), 0xFF000000, {0, GAME_HEIGHT - 200, GAME_WIDTH, 200}, textCache2, false);
}

void DialogOverlay::updateMenu(const uint8_t *keys)
{
    if(timeout > 0)
    {
        --timeout;
        return;
    }
    
    if(keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_SPACE])
    {
        timeout = 10; // Wait this amount of time before advancing again
        // advance text
        int fnl = (int) text.find("\n");
        std::string rest = text.substr(fnl + 1);
        int snl = (int) rest.find("\n");
        rest = rest.substr(snl + 1);
        int tnl = (int) rest.find("\n");
        if(fnl > 0 && tnl > 0) text = text.substr(fnl + 1);
        else dialogOver = true;
        
        if(dialogOver)
        {
            // Give player his inControl back?
            window->level->getLocalPlayer()->inControl = true;
        }
        
        deleteTexture(textCache1);
        textCache1 = textCache2;
        textCache2.id = 0;
    }
}

void DialogOverlay::onOpen()
{
    
}

void DialogOverlay::onClose()
{
    
}
