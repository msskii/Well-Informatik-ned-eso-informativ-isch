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

namespace Multiplayer
{
    
    typedef struct ServerClient
    {
        TCPsocket socket = NULL; // The socket to receive data from & send it to
        int clientID = 0; // The id of this client. Also it's index in the vector
        bool active = true; // Socket is still connected
        // Other stuff will go here like name, id and such
    } ServerClient;
    
    class Server
    {
    private:
        friend int handleSocket(void *data);
        std::vector<ServerClient> clients;
        
    public:
        TCPsocket serversocket;
        
    public:
        Server();
    };
    
}

#endif /* Server_hpp */
