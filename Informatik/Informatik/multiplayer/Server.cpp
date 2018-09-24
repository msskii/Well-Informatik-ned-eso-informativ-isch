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

void Multiplayer::ServerClient::sendTo(const unsigned char *toSend, int length)
{
    SDLNet_TCP_Send(socket, toSend, length);
}

void Multiplayer::cmd_player(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int dataLength)
{
    if(buffer[5] == 'm')
    {
        // printf("Player moved to position: %d, %d\n", *((uint32_t*) (data + 0)), *((uint32_t*) (data + 4)));
        server->broadcast(client, {(char*) buffer, dataLength});
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
            printf("Client disconnected... (Error of SDLnet: %s)\n", SDLNet_GetError());
            return 0;
        }
        
        uint8_t *msg_data = buffer + 6; // Skip 4 id & 2 cmd bytes

        switch(buffer[4])
        {
            case 'p':
                // Player stuff...
                cmd_player(server, client, buffer, msg_data, amount + 4);
                break;
            default:
                printf("Unknown command: %s\n", buffer);
                break;
        }
        
        //server->broadcastTCP(client, newData, amount + 4); // Send to everybody
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
    
    serverRunning = true;

    printf("[INFO] Started server on port: %d\n", SERVER_PORT);
    
    window->menus.clear(); // No open menus...
    window->level->player->inControl = false;
    
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
                printf("Wrong header... rejected\n");
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
            printf("Client %s connected\n", c->name);

            int len = 0;
            for(size_t i = 0; i < clients.size(); i++) len += 4 * 4 + clients[i]->namelen;
            uint8_t* clientData = (uint8_t*) malloc(len);
            int off = 0;
            for(size_t i = 0; i < clients.size(); i++)
            {
                ((uint32_t*)(clientData + off))[0] = clients[i]->clientID; // ID
                ((uint32_t*)(clientData + off))[1] = clients[i]->x; // X
                ((uint32_t*)(clientData + off))[2] = clients[i]->y; // Y
                ((uint32_t*)(clientData + off))[3] = clients[i]->namelen; // len
                memcpy(clientData + off + 16, clients[i]->name, clients[i]->namelen);
                off += 4 * 4 + clients[i]->namelen;
            }

            TCP_Packet p = (createServerPacket(CMD_PLAYER_JOIN, (char*) clientData, len));
            SDLNet_TCP_Send(client, p.data, p.dataLen);
            free(p.data);
            
            clientData = (uint8_t*) realloc(clientData, 4 * 4 + c->namelen);
            ((uint32_t*)(clientData))[0] = c->clientID; // ID
            ((uint32_t*)(clientData))[1] = c->x; // X
            ((uint32_t*)(clientData))[2] = c->y; // Y
            ((uint32_t*)(clientData))[3] = c->namelen; // len
            memcpy(clientData + 16, c->name, c->namelen);
            p = createServerPacket(CMD_PLAYER_JOIN, (char*) clientData, 16 + c->namelen);
            sendToAll(p);
            free(p.data);
            
            clients.push_back(c);
            void ** t = new void*[2]{ (void*) this, (void*) clients[clients.size() - 1] };
            SDL_CreateThread(Multiplayer::handleSocket, "ClientThread", t);
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
    for(int i = 0; i < (int) clients.size(); i++) SDLNet_TCP_Send(clients[i]->socket, packet.data, packet.dataLen);
}

void Multiplayer::Server::broadcast(ServerClient *sender, TCP_Packet packet)
{
    for(int i = 0; i < (int) clients.size(); i++)
    {
        if(clients[i]->socket == sender->socket) continue; // Skip the sender
        SDLNet_TCP_Send(clients[i]->socket, packet.data, packet.dataLen);
    }
}

Multiplayer::TCP_Packet Multiplayer::createPacket(const char *cmd, const char *data, int dataLen)
{
    uint8_t* d = (uint8_t*) malloc(dataLen + 2);
    memcpy(d, cmd, 2);
    memcpy(d + 2, data, dataLen);
    Multiplayer::TCP_Packet packet;
    packet.data = (char*) d;
    packet.dataLen = dataLen + 2;
    
    return packet;
}

Multiplayer::TCP_Packet Multiplayer::Server::createServerPacket(const char *cmd, const char *data, int dataLen)
{
    uint8_t* d = (uint8_t*) malloc(dataLen + 6);
    memset(d, 0, 4);
    memcpy(d + 4, cmd, 2);
    memcpy(d + 6, data, dataLen);
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
