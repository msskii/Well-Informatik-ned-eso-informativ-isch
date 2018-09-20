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
#include <map>

namespace Multiplayer
{
	extern int clientReceive(void *data); // Client receive handler
    class RemotePlayer;

	class Client
	{
	private:
		TCPsocket socket; // Socket which is connected to the server
		std::map<int, RemotePlayer> otherPlayers;
		friend int clientReceive(void *data);

	public:
        bool connectionEstablished = false;
		Client(const char *address); // Set up stuff & start receiver

		void updatePlayerPos(int x, int y);
		void render(int xoff, int yoff);
	};
}



#endif
