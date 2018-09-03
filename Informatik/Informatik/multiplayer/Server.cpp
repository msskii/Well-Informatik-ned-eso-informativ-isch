//
//  Server.cpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Server.hpp"

void Multiplayer::ServerClient::sendTo(const unsigned char *toSend, int length)
{
    SDLNet_TCP_Send(socket, toSend, length);
}

int Multiplayer::handleSocket(void *data)
{
    Server *server = (Server*) ((void**) data)[0]; // The entire server... Use it to send data
    ServerClient *client = (ServerClient*) ((void**) data)[1]; // The client stuff, receiving end
    // TODO: send & receive of this socket...
    
    printf("Number of client newly connected: %d\n", client->clientID);
    
    uint8_t *buffer = (uint8_t*) malloc(BUFFER_SIZE + 1);
	uint8_t *newData = (uint8_t*)malloc(BUFFER_SIZE + 4);
	((uint32_t*)newData)[0] = client->clientID; // Set the id as the first element, only write to index 4 and onward

    while(client->active)
    {
        int amount = SDLNet_TCP_Recv(client->socket, buffer, BUFFER_SIZE);
        if(amount <= 0)
        {
            client->active = false;
            printf("Client disconnected... (Error of SDLnet: %s)\n", SDLNet_GetError());
            return 0;
        }
        buffer[amount] = 0; // Append null byte

		// new data copy
		memcpy(newData + 4, buffer, amount);
        server->broadcast(client, newData, amount + 4); // Send to everybody
    }
    
    return 0;
}

Multiplayer::Server::Server()
{
    SDL_Init(SDL_INIT_TIMER);
    SDLNet_Init(); // Init networking
    
    IPaddress address;
    SDLNet_ResolveHost(&address, NULL, SERVER_PORT);
    serversocket = SDLNet_TCP_Open(&address);
    
    printf("[INFO] Started server on port: %d\n", SERVER_PORT);
    
    SDL_Event e;
    
    serverRunning = true;
    while(serverRunning)
    {
        TCPsocket client = SDLNet_TCP_Accept(serversocket);
        
        if(client)
        {
            Multiplayer::ServerClient *c = new Multiplayer::ServerClient();
            c->socket = client;
            c->clientID = (int) clients.size();
            c->active = true;

            clients.push_back(c);
            void ** t = new void*[2]{ (void*) this, (void*) clients[clients.size() - 1] };
            SDL_CreateThread(Multiplayer::handleSocket, "ClientThread", t);
        }
        
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_WINDOWEVENT)
            {
                if(e.window.event == SDL_WINDOWEVENT_CLOSE) stopServer();
            }
            else if(e.type == SDL_KEYDOWN)
            {
                if(e.key.keysym.sym == SDLK_ESCAPE) stopServer();
            }
        }
        
        
        // Also: Send data to the correct clients...
        
        SDL_Delay(100); // Sleep 100ms
    }
}

void Multiplayer::Server::sendToAll(const unsigned char* data, int length)
{
    for(int i = 0; i < (int) clients.size(); i++) SDLNet_TCP_Send(clients[i]->socket, data, length);
}

void Multiplayer::Server::broadcast(ServerClient *sender, const unsigned char* data, int length)
{
    for(int i = 0; i < (int) clients.size(); i++)
    {
        if(clients[i]->socket == sender->socket) continue; // Skip the sender
        SDLNet_TCP_Send(clients[i]->socket, data, length);
    }
}

void Multiplayer::Server::stopServer()
{
    serverRunning = false;
    SDLNet_Quit();
    SDL_Quit();
    exit(0);
}
