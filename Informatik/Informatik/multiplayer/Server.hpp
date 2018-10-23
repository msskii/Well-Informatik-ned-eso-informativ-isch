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
#define HEADER_SIZE 6
#define BUFFER_SIZE 1024 * 32

#define CMD_PLAYER_JOIN "pj"
#define CMD_PLAYER_NAME "pn"
#define CMD_PLAYER_LEAVE "pl"
#define CMD_PLAYER_MOVE "pm"
#define CMD_PLAYER_ACTION "pa"
#define CMD_PLAYER_CHAT "pc" // TODO...

#define CMD_ENTITY_SPAWN "ej"
#define CMD_ENTITY_DIE "el"
#define CMD_ENTITY_MOVE "em"
#define CMD_ENTITY_ACTION "ea"

#define CMD_LEVEL_INIT "li"
#define CMD_LEVEL_CHANGE "lc"

#define CMD_PACKET_RECEIVED "co"
#define CMD_SETUP_COMPLETE "cs"

#define HEADER "SONM" // Start of new message
#define FOOTER "WADH" // We are done here

class Window;
class Entity;

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
    
    // Ints
    enum MultiplayerEntities
    {
        SLIME = 0,
        PROJECTILE = 1,
        EXPLOSIVE_PROJECTILE = 2,
        EXPLOSION = 3,
        PLAYER = 4,
        NPCE = 5,
        ITEM = 6
    };
    
    // A basic tcp packet with the length and the data stored
    typedef struct TCP_Packet
    {
        char *data;
        int dataLen;
    } TCP_Packet;
    
    extern TCP_Packet createPacket(const char *cmd, const char* data, int dataLen);
    
    class Server
    {
    private:
        friend int handleSocket(void *data); // 
        std::vector<ServerClient*> clients; // All connected clients
        bool serverRunning = false; // If the server is running
        Window *window; // Local pointer to the window
        
        // All the handler functions for the different commands
        friend void cmd_player(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int len);
        friend void cmd_building(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int len);
        friend void cmd_entity(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int len);
        
    public:
        TCPsocket tcp_server;
        
        void stopServer();
        TCP_Packet createClientPacket(const char *cmd, int clientID, const char* data, int dataLen);
        TCP_Packet createServerPacket(const char *cmd, const char *data, int dataLen);

        void sendToAll(TCP_Packet packet);
        void broadcast(ServerClient *sender, TCP_Packet packet);
        TCP_Packet receivePacket(TCPsocket client, int size);

    public:
        Server(Window *window);
    };
    
}

#endif /* Server_hpp */
