//
//  Client.hpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright � 2018 Aaron Hodel. All rights reserved.
//

#ifndef Client_hpp
#define Client_hpp

#include "../util/SDL_Util.hpp"
#include "RemotePlayer.hpp"
#include "Server.hpp"
#include "Buffer.hpp"
#include <map>

class Window;
class Level;

namespace Multiplayer
{
    class Client;
    
	extern int clientReceive(void *data); // Client receive handler
    class RemotePlayer;

	class Client
	{
	private:
        SDLNet_SocketSet sockets = SDLNet_AllocSocketSet(2); // One tcp, one udp
		TCPsocket tcp_socket; // Socket which is connected to the server
        Window *window = nullptr;
        
        std::map<int, RemotePlayer*> otherPlayers;
		friend int clientReceive(void *data);

	public:
        bool connectionEstablished = false;
        bool timeout = false; // Waiting for ack
        Client(Window *window, const char *address, std::string name); // Set up stuff & start receiver

        friend void checkCommand(Client *c, int amount, uint8_t* buffer, char *cmd, uint32_t uuid, uint8_t *data);
        
        void updatePlayerPos(int xpos, int ypos, uint8_t animationSet, uint8_t anim, uint8_t direction);
		//void render(int xoff, int yoff);
        void addRemotePlayers(Level *level);
        void sendToServer(TCP_Packet packet);
	};
}



#endif
