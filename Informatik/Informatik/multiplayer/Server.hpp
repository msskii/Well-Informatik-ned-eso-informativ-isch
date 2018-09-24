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
#include "Buffer.hpp"
#include <vector>

#define SERVER_PORT 5543
#define BUFFER_SIZE 1024
#define HEADER_SIZE 6

#define CMD_PLAYER_JOIN "pj"
#define CMD_PLAYER_NAME "pn"
#define CMD_PLAYER_LEAVE "pl"
#define CMD_PLAYER_MOVE "pm"

#define CMD_ENTITY_SPAWN "ej"
#define CMD_PLAYER_DIE "el"
#define CMD_ENTITY_MOVE "em"


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
        
        int x = 0, y = 0;
        int namelen;
        char *name;
    } ServerClient;
    
    typedef struct TCP_Packet
    {
        char *data;
        int dataLen;
    } TCP_Packet;
    
    extern TCP_Packet createPacket(const char *cmd, const char* data, int dataLen);
    
    class Server
    {
    private:
        friend int handleSocket(void *data);
        std::vector<ServerClient*> clients;
        bool serverRunning = false;
        Window *window;
        
        friend void cmd_player(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int len);
        TCP_Packet createServerPacket(const char *cmd, const char *data, int dataLen);
    public:
        TCPsocket tcp_server;
        
        void stopServer();
        
        void sendToAll(TCP_Packet packet);
        void broadcast(ServerClient *sender, TCP_Packet packet);
        TCP_Packet receivePacket(TCPsocket client, int size);

    public:
        Server(Window *window);
    };
    
}

#endif /* Server_hpp */
