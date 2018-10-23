//
//  ServerCommandHandlers.hpp
//  Informatik
//
//  Created by Aaron Hodel on 23.10.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef ServerCommandHandlers_hpp
#define ServerCommandHandlers_hpp

#include "Server.hpp"
#include "RemotePlayer.hpp"
#include <map>

namespace Multiplayer
{
    extern int clientID; // 0 is the server
    extern std::map<int, Multiplayer::RemotePlayer*> activePlayers;
    
    extern void cmd_player(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int len);
    extern void cmd_building(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int len);
    extern void cmd_entity(Server *server, ServerClient *client, uint8_t *buffer, uint8_t *data, int len);
}

#endif /* ServerCommandHandlers_hpp */
