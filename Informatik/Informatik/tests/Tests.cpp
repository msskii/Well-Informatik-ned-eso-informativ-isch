#include "Tests.hpp"

void Tests::testAudio()
{
	Mix_Init(MIX_INIT_MP3);
}

void Tests::testSockets()
{
	SDL_Init(SDL_INIT_VIDEO); // Init what here?
	SDLNet_Init();

	IPaddress address;
	SDLNet_ResolveHost(&address, NULL, 5543); // Create listening socket on port 5543
	TCPsocket server = SDLNet_TCP_Open(&address); // Open the server on said address
	TCPsocket client = NULL;

	while(client == NULL) client = SDLNet_TCP_Accept(server);

	const char *data = "Hello World!\n\0";
	SDLNet_TCP_Send(client, data, 14);
}

void Tests::testLevelLoader()
{
	LevelLoader("testlevel.level"); // Test loading level
}