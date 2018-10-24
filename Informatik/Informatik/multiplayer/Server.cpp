//
//  Server.cpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Server.hpp"
#include "../graphics/Window.hpp"
#include "../level/Level.hpp"
#include "ServerCommandHandlers.hpp"

Multiplayer::TCP_Packet Multiplayer::ACK_PKG = Multiplayer::createServerPacket(CMD_PACKET_RECEIVED, "coco", 0);

Multiplayer::MultiplayerEntities getEntityType(Entity *e)
{
    if(dynamic_cast<Slime*>(e) != nullptr) return Multiplayer::SLIME;
    else if(dynamic_cast<Projectile*>(e) != nullptr) return Multiplayer::PROJECTILE;
    else if(dynamic_cast<ExplodingProjectile*>(e) != nullptr) return Multiplayer::EXPLOSIVE_PROJECTILE;
    else if(dynamic_cast<Explosion*>(e) != nullptr) return Multiplayer::EXPLOSION;
    else if(dynamic_cast<Player*>(e) != nullptr) return Multiplayer::PLAYER;
    else if(dynamic_cast<NPC*>(e) != nullptr) return Multiplayer::NPCE;
    else if(dynamic_cast<EntityItem*>(e) != nullptr) return Multiplayer::ITEM;
    else if(dynamic_cast<Fireflies*>(e) != nullptr) return Multiplayer::FIREFLY;

    //printf("Entity type not found... Perhaps the archives are incomplete\n");
    return Multiplayer::PROJECTILE;
}

void Multiplayer::ServerClient::sendTo(const unsigned char *toSend, int length)
{
    SDLNet_TCP_Send(socket, toSend, length);
}

int Multiplayer::handleSocket(void *data)
{
    Server *server = (Server*) ((void**) data)[0]; // The entire server... Use it to send data
    ServerClient *client = (ServerClient*) ((void**) data)[1]; // The client stuff, receiving end
    // TODO: send & receive of this socket...
    
    printf("[INFO] Number of client newly connected: %d\n", client->clientID);
    
	uint8_t *buffer = (uint8_t*) malloc(BUFFER_SIZE);    
    while(client->active)
    {
        int amount = SDLNet_TCP_Recv(client->socket, buffer, BUFFER_SIZE);
        if(amount <= 0)
        {
            client->active = false;
            server->sendToAll(Multiplayer::createClientPacket(CMD_PLAYER_LEAVE, client->clientID, NULL, 0));
            printf("[INFO] Client disconnected... (Error of SDLnet: %s)\n", SDLNet_GetError());
            return 0;
        }
        
        int consumed = 0;
        char *cmd = (char*) malloc(3);
        cmd[2] = 0;
        
        while(consumed < amount)
        {
            while(memcmp(buffer + consumed, HEADER, 4))
            {
                if(++consumed >= BUFFER_SIZE) break; // Wait for header
            }
            if(memcmp(buffer + consumed, HEADER, 4)) break;
            
            int len = consumed;
            while(memcmp(buffer + consumed, FOOTER, 4))
            {
                if(++consumed >= BUFFER_SIZE)
                {
                    memmove(buffer, buffer + len, consumed - len);
                    len = 0;
                    consumed = consumed - len;
                    if(consumed >= BUFFER_SIZE)
                    {
                        printf("[WARN] You are using more buffer space than you have!!!!\n");
                        break;
                    }
                    SDLNet_TCP_Recv(client->socket, buffer + consumed, BUFFER_SIZE - consumed);
                }
            }
            if(memcmp(buffer + consumed, FOOTER, 4)) break;
            
            len = consumed - len; // difference between currently consumed and consumed at the header
            consumed -= len;
            
            int c1 = consumed;
            buffer += c1;
            cmd[0] = buffer[4 + consumed];
            cmd[1] = buffer[5 + consumed];
            
            ((uint32_t*) (buffer + consumed))[0] = client->clientID;
            
            switch(cmd[0])
            {
                case 'p':
                    // Player stuff...
                    cmd_player(server, client, buffer, buffer + 6, len);
                    break;
                case 'e':
                    cmd_entity(server, client, buffer, buffer + 6, len);
                    break;
                case 'b':
                    cmd_building(server, client, buffer, buffer + 6, len);
                    break;
                default:
                    printf("[WARNING] Unknown command: %s\n", buffer);
                    break;
            }
            
            buffer -= c1;
            consumed += len;
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
    window->level->getLocalPlayer()->serverPlayer = true;
    window->level->onServer = true; // This is the level on the server
    window->level->remoteLevel = true; // This is the level on the server

    while(serverRunning)
    {
        TCPsocket client = SDLNet_TCP_Accept(tcp_server);
        
        if(client)
        {
            TCP_Packet joinmsg = receivePacket(client, HEADER_SIZE);
            // printBuffer((uint8_t*) joinmsg.data, joinmsg.dataLen);
            
            // PJAF____
            if(memcmp(joinmsg.data, HEADER, 4) || joinmsg.data[6] != 'A' || joinmsg.data[7] != 'F')
            {
                printf("[WARNING] Wrong header... rejected\n");
                continue;
            }
            
            Multiplayer::ServerClient *c = new Multiplayer::ServerClient();
            
            uint32_t namelen = *((uint32_t*)(joinmsg.data + 8));
            TCP_Packet n = receivePacket(client, namelen + 17); // Receive next packet with name
            n.data[n.dataLen - 1] = 0; // Null terminator
            
            c->namelen = namelen;
            c->name = (char*) (n.data + 14);
            c->name[c->namelen] = 0;
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

            // Send the level (Buildings & such)
            Loader::LevelLoader *loader = new Loader::LevelLoader(window->level);
            filedata level = loader->serializeLevel();
            
            // Pack the level into a packet
            TCP_Packet levelPacket = createServerPacket(CMD_LEVEL_INIT, (const char*) level.data, (uint32_t) level.filesize);

            int sent = 0;
            while(sent < levelPacket.dataLen)
            {
                sent += SDLNet_TCP_Send(client, (const char*) (levelPacket.data + sent), (int) fmin(BUFFER_SIZE, (uint32_t) levelPacket.dataLen - sent)); // Finally send the level
                printf("[INFO] Sending data... %d done\n", sent);
                
                TCP_Packet p = receivePacket(c->socket, BUFFER_SIZE);
                while(memcmp(p.data + 4, CMD_PACKET_RECEIVED, 2)) // Control OK
                {
                    // The client didn't ack???
                    printf("[WARN] No ack (%s)! This might be a lost packet!\n", p.data + 4);
                    p = receivePacket(c->socket, BUFFER_SIZE);
                }
                free(p.data);
            }
            
            free(levelPacket.data);
            
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
            printf("[INFO] Sending %d bytes of client data\n", off);

            // Send all players to the one just connected
            TCP_Packet p = (createServerPacket(CMD_PLAYER_JOIN, (char*) clientData, len));
            SDLNet_TCP_Send(client, p.data, p.dataLen);
            free(p.data);

            // Send all players that one that connected
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
            for(int i = 0; i < (int) window->level->entities.size(); i++)
            {
                uint32_t entSize = window->level->entities[i]->getEntitySize();
                uint8_t* entityData = (uint8_t*) malloc(entSize + 12);
                
                MultiplayerEntities e = getEntityType(window->level->entities[i]);
                
                // Store type & id
                ((uint32_t*) (entityData))[0] = (int) e; // The entity specifier
                ((uint32_t*) (entityData))[1] = window->level->entities[i]->entityID; // The specific entity unique ID
                ((uint32_t*) (entityData))[2] = entSize; // The size of this entity is sent as well
                
                window->level->entities[i]->getSerializedEntity(entityData + 12); // Store entity stuff
                
                // Send entity
                p = createServerPacket(CMD_ENTITY_SPAWN, (char*) entityData, entSize + 12);
                SDLNet_TCP_Send(client, p.data, p.dataLen);
                
                TCP_Packet p2 = receivePacket(c->socket, BUFFER_SIZE);
                while(p2.data[4] != 'c' || p2.data[5] != 'o') // Control OK
                {
                    // THe client didn't ack???
                    printf("[WARN] No ack (%s)! This might be a lost packet!\n", p2.data + 4);
                }
                free(p2.data);
                
                
                // Free the stored data
                free(p.data);
                free(entityData);
            }
            
            // Send the code to start updating the level
            TCP_Packet donePacket = createServerPacket(CMD_SETUP_COMPLETE, nullptr, 0);
            SDLNet_TCP_Send(client, donePacket.data, donePacket.dataLen);

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
    uint8_t* d = (uint8_t*) malloc(dataLen + 10);
    memcpy(d, HEADER, 4);
    memcpy(d + 4, cmd, 2);
    if(dataLen) memcpy(d + 6, data, dataLen);
    memcpy(d + 6 + dataLen, FOOTER, 4); // Copy four bytes into the stream
    Multiplayer::TCP_Packet packet;
    packet.data = (char*) d;
    packet.dataLen = dataLen + 10;
    
    return packet;
}

Multiplayer::TCP_Packet Multiplayer::createClientPacket(const char *cmd, int clientID, const char *data, int dataLen)
{
    uint8_t* d = (uint8_t*) malloc(dataLen + 14);
    memcpy(d, HEADER, 4);
    *((uint32_t*)(d + 4)) = clientID;
    memcpy(d + 8, cmd, 2);
    if(dataLen) memcpy(d + 10, data, dataLen);
    memcpy(d + 10 + dataLen, FOOTER, 4); // Copy four bytes into the stream
    Multiplayer::TCP_Packet packet;
    packet.data = (char*) d;
    packet.dataLen = dataLen + 14;
    
    return packet;
}

Multiplayer::TCP_Packet Multiplayer::createServerPacket(const char *cmd, const char *data, int dataLen)
{
    uint8_t* d = (uint8_t*) malloc(dataLen + 14);
    memcpy(d, HEADER, 4);
    memset(d + 4, 0, 4);
    memcpy(d + 8, cmd, 2);
    if(dataLen) memcpy(d + 10, data, dataLen);
    memcpy(d + 10 + dataLen, FOOTER, 4); // Copy four bytes into the stream
    Multiplayer::TCP_Packet packet;
    packet.data = (char*) d;
    packet.dataLen = dataLen + 14;
    
    return packet;
}

void Multiplayer::Server::stopServer()
{
    serverRunning = false;
    SDLNet_Quit();
    SDL_Quit();
    exit(0);
}
