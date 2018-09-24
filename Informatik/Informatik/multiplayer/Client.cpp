#include "Client.hpp"
#include "../graphics/Window.hpp"

std::mutex playerLock;
std::vector<Multiplayer::RemotePlayer*> playersToAdd;

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
        uint8_t *data = buffer + 6;

        // printf("CMD to execute: %s\n", cmd);
        if(!strcmp(cmd, CMD_PLAYER_MOVE))
        {
            if(!c->otherPlayers[uuid] || !c->otherPlayers[uuid]->connected) continue; // This player is not connected!?
            c->otherPlayers[uuid]->data.x_pos = ((uint32_t*) (data))[0];
            c->otherPlayers[uuid]->data.y_pos = ((uint32_t*) (data))[1];
            
            c->otherPlayers[uuid]->walking = ((uint8_t*) (data + 8))[0];
            c->otherPlayers[uuid]->anim = ((uint8_t*) (data + 8))[1];
            c->otherPlayers[uuid]->direction = ((uint8_t*) (data + 8))[2];
        }
        else if(!strcmp(cmd, CMD_PLAYER_JOIN))
        {
            int off = 0;
            while(off < amount - 6)
            {
                uint32_t id = read<uint32_t>(data);
                c->otherPlayers[id] = new RemotePlayer();
                c->otherPlayers[id]->connected = true;
                c->otherPlayers[id]->data.x_pos = (float) read<uint32_t>(data);
                c->otherPlayers[id]->data.y_pos = (float) read<uint32_t>(data);
                c->otherPlayers[id]->nameLen = (float) read<uint32_t>(data);
                c->otherPlayers[id]->name = (char*) malloc(c->otherPlayers[id]->nameLen + 1);
                memcpy(c->otherPlayers[id]->name, data, c->otherPlayers[id]->nameLen);
                c->otherPlayers[id]->name[c->otherPlayers[id]->nameLen] = 0;
                data += c->otherPlayers[id]->nameLen;
                
                off += 4 * 4 + c->otherPlayers[id]->nameLen;
                
                playerLock.lock();
                playersToAdd.push_back(c->otherPlayers[id]);
                playerLock.unlock();
            }
        }
	}

	return 0;
}

Multiplayer::Client::Client(Window *w, const char *address, std::string name)
{
    window = w;
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

void Multiplayer::Client::updatePlayerPos(int xpos, int ypos, uint8_t animationSet, uint8_t anim, uint8_t direction)
{	    
    uint8_t *dataBuffer = (uint8_t*) malloc(11);
    write<int>(dataBuffer, xpos);
    write<int>(dataBuffer, ypos);
    
    write<uint8_t>(dataBuffer, animationSet); // Walking or not
    write<uint8_t>(dataBuffer, anim); // Animation
    write<uint8_t>(dataBuffer, direction);

    sendToServer(createPacket(CMD_PLAYER_MOVE, (char*) (dataBuffer - 11), 11));
}


void Multiplayer::Client::addRemotePlayers(Level *level)
{
    playerLock.lock();
    for(int i = 0; i < (int) playersToAdd.size(); i++)
    {
        level->addEntity(playersToAdd[i]);
    }
    playersToAdd.clear();
    playerLock.unlock();
}

void Multiplayer::Client::sendToServer(TCP_Packet packet)
{
    SDLNet_TCP_Send(tcp_socket, packet.data, packet.dataLen);
}

