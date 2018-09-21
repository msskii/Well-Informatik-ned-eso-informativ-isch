//
//  Server.hpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Server_hpp
#define Server_hpp

#include "../util/SDL_Util.hpp"
#include <vector>

#define SERVER_PORT 5543
#define BUFFER_SIZE 1024

class Window;

namespace Multiplayer
{
    
    typedef struct ServerClient
    {
        TCPsocket socket = NULL; // The socket to receive data from & send it to
        int clientID = 0; // The id of this client. Also it's index in the vector
        bool active = true; // Socket is still connected
        void sendTo(const unsigned char *toSend, int length); // Send data to just this client
        // Other stuff will go here like name, id and such
    } ServerClient;
    
    class Server
    {
    private:
        friend int handleSocket(void *data);
        std::vector<ServerClient*> clients;
        bool serverRunning = false;
        Window *window;

    public:
        TCPsocket serversocket;
        
        void stopServer();

        void sendToAll(const unsigned char* data, int length);
        void broadcast(ServerClient *sender, const unsigned char* data, int length);
        
    public:
        Server(Window *window);
    };
    
}

#endif /* Server_hpp */
