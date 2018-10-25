//
//  ClientOverlay.cpp
//  Informatik
//
//  Created by Aaron Hodel on 25.10.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "ClientOverlay.hpp"

ClientOverlay::ClientOverlay()
{
    shouldLevelBeUpdated = true;
    textBox = new TextBox("", 0, GAME_HEIGHT - 200, GAME_WIDTH, 200, 0);
}

bool ClientOverlay::shouldWindowClose() { return false; }

void ClientOverlay::renderMenu()
{
    // TODO: Render the chat messages...
    fillRect(0xFFFF00FF, {0, 0, 1, GAME_HEIGHT}); // 500 width?
}

void ClientOverlay::updateMenu(const uint8_t *keys)
{
    bool currentState = keys[SDL_GetScancodeFromKey(GLOBAL_KEY_CONFIG[BUTTON_CHAT])];
    if(currentState && !lastState && !opened)
    {
        // New pressed... Open a textbox
        addElement(textBox);
        shouldLevelBeUpdated = false;
        opened = true;
    }
    
    if(keys[SDL_SCANCODE_ESCAPE] && opened)
    {
        removeElement(textBox);
        shouldLevelBeUpdated = true;
        textBox->currentText = "";
        opened = false;
    }
    
    if(keys[SDL_SCANCODE_RETURN] && opened)
    {
        // printf("[DEBUG] Sending message: %s\n", textBox->currentText.c_str());
        window->level->clientConnector->sendToServer(Multiplayer::createPacket(CMD_PLAYER_CHAT, textBox->currentText.c_str(), (int) textBox->currentText.size()));
        textBox->currentText = "";
        removeElement(textBox);
        shouldLevelBeUpdated = true;
        opened = false;
    }
    
    lastState = currentState;
}

void ClientOverlay::onOpen() {}
void ClientOverlay::onClose() {}
