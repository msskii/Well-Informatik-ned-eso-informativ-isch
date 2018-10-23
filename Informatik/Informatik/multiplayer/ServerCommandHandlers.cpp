//
//  ServerCommandHandlers.cpp
//  Informatik
//
//  Created by Aaron Hodel on 23.10.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "ServerCommandHandlers.hpp"
#include "../graphics/Window.hpp"

int Multiplayer::clientID = 1; // 0 is the server
std::map<int, Multiplayer::RemotePlayer*> Multiplayer::activePlayers; // All the active players on the server

// The handler for player commands
void Multiplayer::cmd_player(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int dataLength)
{
    if(buffer[5] == 'm')
    {
        server->window->level->activePlayerLock.lock();
        activePlayers[client->clientID]->data.x_pos = (float) *((uint32_t*) (data + 0));
        activePlayers[client->clientID]->data.y_pos = (float) *((uint32_t*) (data + 4));
        activePlayers[client->clientID]->walking = *((uint8_t*) (data + 8));
        activePlayers[client->clientID]->anim = *((uint8_t*) (data + 9));
        activePlayers[client->clientID]->direction = *((uint8_t*) (data + 10));
        server->window->level->activePlayerLock.unlock();
        server->broadcast(client, {(char*) buffer, dataLength});
    }
}

// Handler for entity commands
void Multiplayer::cmd_entity(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int dataLength)
{
    if(buffer[5] == 'm')
    {
        server->broadcast(client, {(char*) buffer, dataLength}); // Send the data to all
    }
}

// Handler for the Building commands
void Multiplayer::cmd_building(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int dataLength)
{
    if(buffer[5] == 'a')
    {
        // Shouldnt happen
        server->broadcast(client, {(char*) buffer, dataLength}); // Send the data to all
    }
}
