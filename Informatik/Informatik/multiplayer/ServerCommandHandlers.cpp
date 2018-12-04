//
//  ServerCommandHandlers.cpp
//  Informatik
//
//  Created by Aaron Hodel on 23.10.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "ServerCommandHandlers.hpp"
#include "../graphics/Window.hpp"
#include "Server.hpp"

int Multiplayer::clientID = 1; // 0 is the server
std::map<int, Multiplayer::RemotePlayer*> Multiplayer::activePlayers; // All the active players on the server

Entity *Multiplayer::deserializeEntity(uint8_t *data)
{
    Multiplayer::MultiplayerEntities entityNum = (Multiplayer::MultiplayerEntities) read<int>(data); // The type
    int entityID = read<int>(data); // Entity ID
    int entitySize = read<int>(data); // Size in bytes of this entity
    printf("[INFO] Entity with type: %d and id %d and Size %d spawned\n", entityNum, entityID, entitySize);
    
    Entity *e = nullptr;
    EntityData d = read<EntityData>(data);
    
    switch(entityNum)
    {
        case Multiplayer::SLIME:
            e = new Slime(d.x_pos, d.y_pos, (int) d.maxhealth);
            break;
        case Multiplayer::PROJECTILE:
            e = new Projectile(((float*) data)[0], ((float*) data)[1], ((float*) data)[2]);
            break;
        case Multiplayer::PLAYER:
            e = nullptr;
            break;
        case Multiplayer::NPCE:
            printf("Constructing new NPC...\n");
            e = new NPC(data - sizeof(EntityData));
            break;
        case Multiplayer::ITEM:
        {
            //printBuffer(data, 0x20);
            //need to fix to id, ids are easier because switchstatements work with them so we can set size and additional factors
            
            //char *name = readString(data);
            //e = new EntityItem((int) d.x_pos / TILE_SIZE, (int) d.y_pos / TILE_SIZE, new Item(name));
            
            char *name = readString(data);
            e = new EntityItem((int) d.x_pos / TILE_SIZE, (int) d.y_pos / TILE_SIZE, 0);
        }
            break;
        case Multiplayer::FIREFLY:
            e = new Fireflies(d.x_pos, d.y_pos);
            break;
        default:
            //printf("Entity type %d not found... Perhaps the archives are incomplete\n", type);
            e = new Projectile(d.x_pos, d.y_pos, 0);
            break;
    }
    if(e) e->entityID = entityID;
    return e;
}

void Multiplayer::waitForAck(TCPsocket socket, Server *server)
{
    
    TCP_Packet p2 = server->receivePacket(socket, BUFFER_SIZE);
    while(p2.data[4] != 'c' || p2.data[5] != 'o') // Control OK
    {
        // THe client didn't ack???
        printf("[WARN] No ack (%s)! This might be a lost packet!\n", p2.data + 4);
    }
    free(p2.data);
}

// The handler for player commands
void Multiplayer::cmd_player(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int dataLength)
{
    if(buffer[5] == 'm') // move
    {
        server->window->level->activePlayerLock.lock();
        activePlayers[client->clientID]->data.x_pos = (float) *((uint32_t*) (data + 0));
        activePlayers[client->clientID]->data.y_pos = (float) *((uint32_t*) (data + 4));
        activePlayers[client->clientID]->walking = *((uint8_t*) (data + 8));
        activePlayers[client->clientID]->anim = *((uint8_t*) (data + 9));
        activePlayers[client->clientID]->direction = *((uint8_t*) (data + 10));
        server->window->level->activePlayerLock.unlock();
        server->broadcast(client, Multiplayer::createClientPacket(CMD_PLAYER_MOVE, client->clientID, (char*) data, 11));
    }
    else if(buffer[5] == 'c') // Chat
    {
        // const char *str = readString(data);
        server->sendToAll(Multiplayer::createClientPacket(CMD_PLAYER_CHAT, client->clientID, (char*) (buffer + 6), dataLength));
    }
}

// Handler for entity commands
void Multiplayer::cmd_entity(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int dataLength)
{
    if(buffer[5] == 'm') // Move Entity
    {
        server->broadcast(client, {(char*) buffer, dataLength}); // Send the data to all
    }
    else if(buffer[5] == 'j') // Spawn Entity
    {
        server->window->level->entityLock.lock();
        server->window->level->serverAdded.push_back(deserializeEntity(buffer + 6));
        server->window->level->entityLock.unlock();
        server->broadcast(client, Multiplayer::createClientPacket(CMD_ENTITY_SPAWN, client->clientID, (char*) data, dataLength));
    }
    else if(buffer[5] == 'l') // Delete entity (Leave)
    {
        buffer += 6;
        server->window->level->entityLock.lock();
        int eid = read<int>(buffer);
        server->window->level->serverRemoved.push_back(eid);
        server->window->level->entityLock.unlock();
        server->broadcast(client, Multiplayer::createClientPacket(CMD_ENTITY_DIE, client->clientID, (char*) data, dataLength));
        client->sendTo((uint8_t*) ACK_PKG.data, ACK_PKG.dataLen);
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
