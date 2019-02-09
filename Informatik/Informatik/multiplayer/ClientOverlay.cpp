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
    textBox = new TextBox("", 0, GAME_HEIGHT - 100, GAME_WIDTH / 2, 100, 0);
    textBox->getFocus();
}

bool ClientOverlay::shouldWindowClose() { return false; }

void ClientOverlay::renderMenu()
{
    // TODO: Render the chat messages...
    // fillRect(0xFFFFFFFF, {0, 0, CHAT_WIDTH, GAME_HEIGHT}); // 500 width?
    fillRect(0x7F7F7F7F, {0, GAME_HEIGHT - 100 - 100 * (int) messages.size(), CHAT_WIDTH, 100 * (int) messages.size()});
}



void ClientOverlay::updateMenu(const uint8_t *keys)
{
    for(uint32_t i = 0; i < messages.size(); i++)
    {
        if(messages[i].disappearTimer-- <= 0)
        {
            removeElement(messages[i].text);
            messages.erase(messages.begin() + i--);
            // for(unsigned int j = 0; j < messages.size(); j++) messages[j].text->y -= 200;
        }
    }
    
    bool currentState = keys[SDL_GetScancodeFromKey(GLOBAL_KEY_CONFIG[BUTTON_CHAT])];
    if(currentState && !lastState && !opened)
    {
        // New pressed... Open a textbox
        addElement(textBox);
        //shouldLevelBeUpdated = false;
        opened = true;
        printf("[INFO] You have opened the chat\n");
    }
    
    if(keys[SDL_SCANCODE_ESCAPE] && opened)
    {
        removeElement(textBox);
        //shouldLevelBeUpdated = true;
        textBox->currentText = "";
        opened = false;
    }
    
    if(keys[SDL_SCANCODE_RETURN] && opened)
    {
        printf("[DEBUG] Sending message: %s\n", textBox->currentText.c_str());
        uint8_t *buffer = (uint8_t*) malloc((int) textBox->currentText.size() + 4);
        ((uint32_t*)buffer)[0] = (int) textBox->currentText.size();
        memcpy(buffer + 4, textBox->currentText.c_str(), textBox->currentText.size());
        window->level->clientConnector->sendToServer(Multiplayer::createPacket(CMD_PLAYER_CHAT, (char*) buffer, (int) textBox->currentText.size() + 4));
        free(buffer);
        textBox->currentText = "";
        removeElement(textBox);
        //shouldLevelBeUpdated = true;
        opened = false;
    }
    
    lastState = currentState;
}

void ClientOverlay::addMessage(std::string text)
{
    for(uint32_t i = 0; i < messages.size(); i++) messages[i].text->y -= 100;
    printf("Text from chat: %s\n", text.c_str());
    Text *elmnt = new Text(text.c_str(), 0, GAME_HEIGHT - 200, CHAT_WIDTH, 100);
    addElement(elmnt);
    messages.push_back({ elmnt });
}

void ClientOverlay::onOpen() {}
void ClientOverlay::onClose() {}
