#include "Client.hpp"

int Multiplayer::clientReceive(void *data)
{
	Multiplayer::Client* c = (Multiplayer::Client*) data;

    char *cmd = (char*) malloc(3);
    cmd[2] = 0;
	uint8_t *buffer = new uint8_t[BUFFER_SIZE + 1];
	while (true)
	{
		int amount = SDLNet_TCP_Recv(c->tcp_socket, buffer, BUFFER_SIZE);
		if (amount <= 0)
		{
			// Some error occured, exit
			printf("[ERROR] Connection to server lost!\n");
			exit(0);
		}
        
        buffer[amount] = 0;
        
        uint32_t uuid = *((uint32_t*)buffer);
        cmd[0] = buffer[4];
        cmd[1] = buffer[5];

        if(!strcmp(cmd, CMD_PLAYER_MOVE))
        {
            printf("Moving player\n");
            c->otherPlayers[uuid].data.x_pos = ((uint32_t*) (buffer + 6))[0];
            c->otherPlayers[uuid].data.y_pos = ((uint32_t*) (buffer + 6))[1];
        }
	}

	return 0;
}

Multiplayer::Client::Client(const char *address, std::string name)
{
	SDLNet_Init();

	IPaddress ip;
	SDLNet_ResolveHost(&ip, address, SERVER_PORT);
	tcp_socket = SDLNet_TCP_Open(&ip); // Connect to server...
    
	if (tcp_socket == NULL)
	{
		printf("[ERROR] Couldn't connect to the server '%s' (SDLnet error: %s)\n", address, SDLNet_GetError());
		// exit(0);
        return;
	}
    
    SDLNet_TCP_AddSocket(sockets, tcp_socket);

    connectionEstablished = true;
    
	uint8_t *welcome = new uint8_t[6] { 0x41, 0x46 }; // Send welcoming message? --> Like name or stuff
    *((uint32_t*) (welcome + 2)) = (uint32_t) name.size();
    sendToServer(createPacket(CMD_PLAYER_JOIN, (char*) welcome, HEADER_SIZE));
    sendToServer(createPacket(CMD_PLAYER_NAME, name.c_str(), (int) name.size()));

	SDL_CreateThread(clientReceive, "ClientReceiverTCP", this);
}

void Multiplayer::Client::updatePlayerPos(int xpos, int ypos)
{	    
    uint8_t *dataBuffer = (uint8_t*) malloc(8);
    write<int>(dataBuffer, xpos);
    write<int>(dataBuffer, ypos);
    sendToServer(createPacket(CMD_PLAYER_MOVE, (char*) (dataBuffer - 8), 8));
}

void Multiplayer::Client::render(int xoff, int yoff)
{
	for (auto it = otherPlayers.begin(); it != otherPlayers.end(); it++)
	{
		it->second.render(xoff, yoff);
	}
}

void Multiplayer::Client::sendToServer(TCP_Packet packet)
{
    SDLNet_TCP_Send(tcp_socket, packet.data, packet.dataLen);
}

