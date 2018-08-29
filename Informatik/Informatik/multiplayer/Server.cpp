//
//  Server.cpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Server.hpp"

int Multiplayer::handleSocket(void *data)
{
    Server *server = (Server*) ((void**) data)[0]; // The entire server... Use it to send data
    ServerClient *client = (ServerClient*) ((void**) data)[1]; // The client stuff, receiving end
    // TODO: send & receive of this socket...
    
    printf("Number of client: %d\n", client->clientID);
    
    uint8_t *buffer = (uint8_t*) malloc(BUFFER_SIZE + 1);
    
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
        printf("Received data: %s", buffer); // Print data
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
    
    while(true)
    {
        TCPsocket client = SDLNet_TCP_Accept(serversocket);
        
        if(client)
        {
            ServerClient c = { client, (int) clients.size(), true };
            clients.push_back(c);
            void ** t = new void*[2]{ (void*) this, (void*) &clients[clients.size() - 1] };
            SDL_CreateThread(Multiplayer::handleSocket, "ClientThread", t);
        }
        
        // Also: Send data to the correct clients...
        
        SDL_Delay(100); // Sleep 100ms
    }
}
