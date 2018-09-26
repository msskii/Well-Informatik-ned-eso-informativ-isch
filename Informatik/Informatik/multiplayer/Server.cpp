//
//  Server.cpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Server.hpp"
#include "../graphics/Window.hpp"

int clientID = 1; // 0 is the server
std::map<int, Multiplayer::RemotePlayer*> activePlayers;

Multiplayer::MultiplayerEntities getEntityType(Entity *e)
{
    if(dynamic_cast<Slime*>(e) != nullptr) return Multiplayer::SLIME;
    else if(dynamic_cast<Projectile*>(e) != nullptr) return Multiplayer::PROJECTILE;
    else if(dynamic_cast<ExplodingProjectile*>(e) != nullptr) return Multiplayer::EXPLOSIVE_PROJECTILE;
    else if(dynamic_cast<Explosion*>(e) != nullptr) return Multiplayer::EXPLOSION;
    else if(dynamic_cast<Player*>(e) != nullptr) return Multiplayer::PLAYER;

    //printf("Entity type not found... Perhaps the archives are incomplete\n");
    return Multiplayer::PROJECTILE;
}

int Multiplayer::getEntitySize(MultiplayerEntities e)
{
   switch(e)
    {
        case SLIME: return 6 * 4;
        case PROJECTILE: return 5 * 4;
        default: return 5 * 4;
    }
}

Entity *Multiplayer::createEntityFromData(Multiplayer::MultiplayerEntities type, uint8_t *data)
{
    switch(type)
    {
        case Multiplayer::SLIME:
            return new Slime((float) ((uint32_t*) data)[0], (float) ((uint32_t*) data)[1], ((uint32_t*) data)[2]);
        case Multiplayer::PROJECTILE:
            return new Projectile(((float*) data)[0], ((float*) data)[1], ((float*) data)[2]);
        case Multiplayer::PLAYER:
            return nullptr;
        default:
            //printf("Entity type %d not found... Perhaps the archives are incomplete\n", type);
            return new Projectile(((float*) data)[0], ((float*) data)[1], ((float*) data)[2]);
    }
}

void Multiplayer::ServerClient::sendTo(const unsigned char *toSend, int length)
{
    SDLNet_TCP_Send(socket, toSend, length);
}

void Multiplayer::cmd_player(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int dataLength)
{
    if(buffer[5] == 'm')
    {
        // printf("Player moved to position: %d, %d\n", *((uint32_t*) (data + 0)), *((uint32_t*) (data + 4)));
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

void Multiplayer::cmd_entity(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int dataLength)
{
    if(buffer[5] == 'm')
    {
        server->broadcast(client, {(char*) buffer, dataLength}); // Send the data to all
    }
}

void Multiplayer::cmd_building(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int dataLength)
{
    if(buffer[5] == 'a')
    {
        // Shouldnt happen
        server->broadcast(client, {(char*) buffer, dataLength}); // Send the data to all
    }
}

int Multiplayer::handleSocket(void *data)
{
    Server *server = (Server*) ((void**) data)[0]; // The entire server... Use it to send data
    ServerClient *client = (ServerClient*) ((void**) data)[1]; // The client stuff, receiving end
    // TODO: send & receive of this socket...
    
    printf("Number of client newly connected: %d\n", client->clientID);
    
	uint8_t *buffer = (uint8_t*) malloc(BUFFER_SIZE + 4);
	((uint32_t*)buffer)[0] = client->clientID; // Set the id as the first element, only write to index 4 and onward
    
    while(client->active)
    {
        int amount = SDLNet_TCP_Recv(client->socket, buffer + 4, BUFFER_SIZE);
        if(amount <= 0)
        {
            client->active = false;
            server->sendToAll(server->createClientPacket(CMD_PLAYER_LEAVE, client->clientID, NULL, 0));
            printf("[INFO] Client disconnected... (Error of SDLnet: %s)\n", SDLNet_GetError());
            return 0;
        }
        
        uint8_t *msg_data = buffer + 6; // Skip 4 id & 2 cmd bytes

        switch(buffer[4])
        {
            case 'p':
                // Player stuff...
                cmd_player(server, client, buffer, msg_data, amount + 4);
                break;
            case 'e':
                cmd_entity(server, client, buffer, msg_data, amount + 4);
                break;
            case 'b':
                cmd_building(server, client, buffer, msg_data, amount + 4);
                break;
            default:
                printf("[WARNING] Unknown command: %s\n", buffer);
                break;
        }        
    }
    
    return 0;
}

Multiplayer::Server::Server(Window *w) : window(w)
{
    SDL_Init(SDL_INIT_TIMER);
    SDLNet_Init(); // Init networking
    
    IPaddress address;
    SDLNet_ResolveHost(&address, NULL, SERVER_PORT);
    tcp_server = SDLNet_TCP_Open(&address);
    
    if(!tcp_server)
    {
        printf("[ERROR] Couldn't create server... %s\n", SDLNet_GetError());
        printf("[ERROR] Is something already running on that port?\n");
        exit(0);
    }
    
    serverRunning = true;

    printf("[INFO] Started server on port: %d\n", SERVER_PORT);
    
    window->menus.clear(); // No open menus...
    window->level->server = this;
    window->level->getLocalPlayer()->inControl = false;
    window->level->onServer = true; // This is the level on the server
    window->level->remoteLevel = true; // This is the level on the server

    while(serverRunning)
    {
        TCPsocket client = SDLNet_TCP_Accept(tcp_server);
        
        if(client)
        {
            //SDLNet_TCP_Recv(client, greetings, HEADER_SIZE);
            TCP_Packet joinmsg = receivePacket(client, HEADER_SIZE);
            // printBuffer((uint8_t*) joinmsg.data, joinmsg.dataLen);

            // PJAF____
            if(joinmsg.data[2] != 'A' || joinmsg.data[3] != 'F')
            {
                printf("[WARNING] Wrong header... rejected\n");
                continue;
            }
            
            Multiplayer::ServerClient *c = new Multiplayer::ServerClient();
            
            uint32_t namelen = *((uint32_t*)(joinmsg.data + 4));
            TCP_Packet n = receivePacket(client, namelen + 1);
            n.data[n.dataLen - 1] = 0;
            // printBuffer((uint8_t*) n.data, n.dataLen);
            
            c->namelen = namelen;
            c->name = (char*) (n.data + 2);
            c->socket = client;
            c->clientID = clientID++;
            c->active = true;
            free(joinmsg.data);

            clients.push_back(c);
            activePlayers[c->clientID] = new RemotePlayer();
            // We're on the main thread
            window->level->activePlayerLock.lock();
            window->level->addEntity(activePlayers[c->clientID]); // Same pointer
            window->level->activePlayers.push_back(activePlayers[c->clientID]); // Same pointer
            window->level->activePlayerLock.unlock();

            // Sync players on server & on clients
            int len = 0;
            for(size_t i = 0; i < clients.size(); i++) if(clients[i]->active && clients[i]->clientID != c->clientID) len += 4 * 4 + clients[i]->namelen;
            uint8_t* clientData = (uint8_t*) malloc(len);
            int off = 0;
            for(size_t i = 0; i < clients.size(); i++)
            {
                if(!clients[i]->active || clients[i]->clientID == c->clientID) continue;
                ((uint32_t*)(clientData + off))[0] = clients[i]->clientID; // ID
                ((uint32_t*)(clientData + off))[1] = clients[i]->x; // X
                ((uint32_t*)(clientData + off))[2] = clients[i]->y; // Y
                ((uint32_t*)(clientData + off))[3] = clients[i]->namelen; // len
                memcpy(clientData + off + 16, clients[i]->name, clients[i]->namelen);
                off += 4 * 4 + clients[i]->namelen;
            }
            printf("Sending %d bytes of client data\n", off);

            // Send all players to the one just connected
            TCP_Packet p = (createServerPacket(CMD_PLAYER_JOIN, (char*) clientData, len));
            SDLNet_TCP_Send(client, p.data, p.dataLen);
            free(p.data);

            // Send all players that one connected
            clientData = (uint8_t*) realloc(clientData, 4 * 4 + c->namelen);
            ((uint32_t*)(clientData))[0] = c->clientID; // ID
            ((uint32_t*)(clientData))[1] = c->x; // X
            ((uint32_t*)(clientData))[2] = c->y; // Y
            ((uint32_t*)(clientData))[3] = c->namelen; // len
            memcpy(clientData + 16, c->name, c->namelen);
            p = createServerPacket(CMD_PLAYER_JOIN, (char*) clientData, 16 + c->namelen);
            broadcast(c, p);
            free(p.data);
            
            // Send entity data..
            int entityLen = 0;
            for(int i = 0; i < (int) window->level->entities.size(); i++) entityLen += getEntitySize(getEntityType(window->level->entities[i]));
            uint8_t* entityData = (uint8_t*) malloc(entityLen);
            off = 0;
            for(int i = 0; i < (int) window->level->entities.size(); i++)
            {
                MultiplayerEntities e = getEntityType(window->level->entities[i]);
                ((uint32_t*) (entityData + off))[0] = (int) e;
                ((uint32_t*) (entityData + off))[1] = window->level->entities[i]->entityID;
                off += 8;
                
                switch(e)
                {
                    case SLIME:
                        ((uint32_t*) (entityData + off))[0] = (int) window->level->entities[i]->data.x_pos;
                        ((uint32_t*) (entityData + off))[1] = (int) window->level->entities[i]->data.y_pos;
                        ((uint32_t*) (entityData + off))[2] = (int) ((Slime*) window->level->entities[i])->enemy_level;
                        ((uint32_t*) (entityData + off))[3] = (int) ((Slime*) window->level->entities[i])->anim;
                        off += 4 * 4;
                        break;
                    default:
                        ((float*) (entityData + off))[0] = window->level->entities[i]->data.x_pos;
                        ((float*) (entityData + off))[1] = window->level->entities[i]->data.y_pos;
                        ((float*) (entityData + off))[2] = 0;
                        off += 3 * 4;
                        break;
                }
            }

            p = createServerPacket(CMD_ENTITY_SPAWN, (char*) entityData, entityLen);
            SDLNet_TCP_Send(client, p.data, p.dataLen);
            free(p.data);

            uint8_t* buildingData = (uint8_t*) malloc(2 * 4 + 1 * 2);
            for(int i = 0; i < (int) window->level->buildings.size(); i++)
            {
                ((uint32_t*) buildingData)[0] = window->level->buildings[i]->data.xcoord;
                ((uint32_t*) buildingData)[1] = window->level->buildings[i]->data.ycoord;
                ((uint16_t*) (buildingData + 8))[0] = window->level->buildings[i]->data.buildingNumber;
                p = createServerPacket(CMD_BUILDING_ADD, (char*) buildingData, 2 * 4 + 1 * 2);
                int sent = SDLNet_TCP_Send(client, p.data, p.dataLen);
                if(sent != p.dataLen)
                {
                    printf("[WARN] Couldnt send building data... Just %d out of %d bytes were sent\n", sent, p.dataLen);
                }
                free(p.data);
            }
            free(buildingData);
            
            void ** t = new void*[2]{ (void*) this, (void*) clients[clients.size() - 1] };
            SDL_CreateThread(Multiplayer::handleSocket, "ClientThread", t);
        }
        
        for(int i = 0; i < (int) clients.size(); i++)
        {
            if(!clients[i]->active) clients.erase(clients.begin() + i); // Remove clients who've disconnected... (Thread should be done anyway)
        }
        
        window->nextFrame(); // Render & update & events
    }
}

Multiplayer::TCP_Packet Multiplayer::Server::receivePacket(TCPsocket client, int size)
{
    Multiplayer::TCP_Packet packet;
    packet.data = (char*) malloc(size + 2);
    packet.dataLen = size + 2;
    
    SDLNet_TCP_Recv(client, packet.data, packet.dataLen);
    
    return packet;
}

void Multiplayer::Server::sendToAll(TCP_Packet packet)
{
    for(int i = 0; i < (int) clients.size(); i++) if(clients[i]->active) SDLNet_TCP_Send(clients[i]->socket, packet.data, packet.dataLen);
}

void Multiplayer::Server::broadcast(ServerClient *sender, TCP_Packet packet)
{
    for(int i = 0; i < (int) clients.size(); i++)
    {
        if(clients[i]->socket == sender->socket || !clients[i]->active) continue; // Skip the sender
        SDLNet_TCP_Send(clients[i]->socket, packet.data, packet.dataLen);
    }
}

Multiplayer::TCP_Packet Multiplayer::createPacket(const char *cmd, const char *data, int dataLen)
{
    uint8_t* d = (uint8_t*) malloc(dataLen + 2);
    memcpy(d, cmd, 2);
    if(dataLen) memcpy(d + 2, data, dataLen);
    Multiplayer::TCP_Packet packet;
    packet.data = (char*) d;
    packet.dataLen = dataLen + 2;
    
    return packet;
}

Multiplayer::TCP_Packet Multiplayer::Server::createClientPacket(const char *cmd, int clientID, const char *data, int dataLen)
{
    uint8_t* d = (uint8_t*) malloc(dataLen + 6);
    *((uint32_t*)(d)) = clientID;
    memcpy(d + 4, cmd, 2);
    if(dataLen) memcpy(d + 6, data, dataLen);
    Multiplayer::TCP_Packet packet;
    packet.data = (char*) d;
    packet.dataLen = dataLen + 6;
    
    return packet;
}

Multiplayer::TCP_Packet Multiplayer::Server::createServerPacket(const char *cmd, const char *data, int dataLen)
{
    uint8_t* d = (uint8_t*) malloc(dataLen + 6);
    memset(d, 0, 4);
    memcpy(d + 4, cmd, 2);
    if(dataLen) memcpy(d + 6, data, dataLen);
    Multiplayer::TCP_Packet packet;
    packet.data = (char*) d;
    packet.dataLen = dataLen + 6;
    
    return packet;
}

void Multiplayer::Server::stopServer()
{
    serverRunning = false;
    SDLNet_Quit();
    SDL_Quit();
    exit(0);
}
