#include "Client.hpp"

int Multiplayer::clientReceive(void *data)
{
	Multiplayer::Client* c = (Multiplayer::Client*) data;

	uint8_t *buffer = new uint8_t[BUFFER_SIZE];
	while (true)
	{
		int amount = SDLNet_TCP_Recv(c->socket, buffer, BUFFER_SIZE);
		if (amount <= 0)
		{
			// Some error occured, exit
			printf("[ERROR] Connection to server lost!\n");
			exit(0);
		}

		if (amount == 12)
		{
			// 3 ints
			uint32_t id = ((uint32_t*)buffer)[0];
			uint32_t x = ((uint32_t*)buffer)[1];
			uint32_t y = ((uint32_t*)buffer)[2];

			c->otherPlayers[id].data.x_pos = (float) x;
			c->otherPlayers[id].data.y_pos = (float) y;
		}
	}

	return 0;
}

Multiplayer::Client::Client(const char *address)
{
	SDLNet_Init();

	IPaddress ip;
	SDLNet_ResolveHost(&ip, address, SERVER_PORT);
	socket = SDLNet_TCP_Open(&ip); // Connect to server...

	if (socket == NULL)
	{
		printf("[ERROR] Couldn't connect to the server '%s' (SDLnet error: %s)\n", address, SDLNet_GetError());
		exit(0);
	}

	uint8_t *welcome = new uint8_t[2] { 0x41, 0x46 }; // Send welcoming message? --> Like name or stuff
	SDLNet_TCP_Send(socket, (char*) welcome, 2);

	SDL_CreateThread(clientReceive, "ClientReceiver", this);
}

void Multiplayer::Client::updatePlayerPos(int xpos, int ypos)
{	
	uint8_t *dataBuffer = (uint8_t*) malloc(4 + 4); // send 8 bytes

	((uint32_t*)dataBuffer)[0] = xpos;
	((uint32_t*)dataBuffer)[1] = ypos;
	SDLNet_TCP_Send(socket, dataBuffer, 8); // Send data buffer

	free(dataBuffer);
}	

void Multiplayer::Client::render(SDL_Renderer *renderer, int xoff, int yoff)
{
	for (auto it = otherPlayers.begin(); it != otherPlayers.end(); it++)
	{
		it->second.render(renderer, xoff, yoff);
	}
}