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
    
}

bool DialogOverlay::shouldWindowClose()
{
    return dialogOver;
}

void DialogOverlay::renderMenu(SDL_Renderer *renderer)
{
    COLOR(renderer, 0xFFFFFFFF);
    SDL_Rect dst = {0, GAME_HEIGHT - 400, GAME_WIDTH, 400};
    SDL_RenderFillRect(renderer, &dst);
    
    int fnl = (int) text.find("\n");
    std::string line1 = text.substr(0, fnl);
    std::string rest = text.substr(fnl + 1);
    int snl = (int) rest.find("\n");
    std::string line2 = rest.substr(0, snl);
    if(textCache1.texture == nullptr) drawTextAspect(renderer, line1.c_str(), 0xFF000000, 0, GAME_HEIGHT - 400, GAME_WIDTH, 200, textCache1);
    else
    {
        SDL_Rect r = {0, GAME_HEIGHT - 400, textCache1.textwidth, textCache1.textheight};
        SDL_RenderCopy(renderer, textCache1.texture, NULL, &r);
    }
    
    if(fnl > 0)
    {
        if(textCache2.texture == nullptr) drawTextAspect(renderer, line2.c_str(), 0xFF000000, 0, GAME_HEIGHT - 200, GAME_WIDTH, 200, textCache2);
        else
        {
            SDL_Rect r = {0, GAME_HEIGHT - 200, textCache2.textwidth, textCache2.textheight};
            SDL_RenderCopy(renderer, textCache2.texture, NULL, &r);
        }
    }
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
    }
}

void DialogOverlay::drawOverlay(SDL_Renderer *renderer) {}


void DialogOverlay::onOpen()
{
    
}

void DialogOverlay::onClose()
{
    
}
