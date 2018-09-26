#include "Client.hpp"
#include "../graphics/Window.hpp"

std::mutex playerLock;
std::vector<Multiplayer::RemotePlayer*> playersToAdd;
std::vector<Multiplayer::RemotePlayer*> playersToRemove;

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
        uint8_t *data = buffer + 6; // 4 for uuid + 2 for cmd

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
                if(id == 0) break; // Server id... Restricted
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
                printf("[INFO] Player %d joined\n", id);
                playersToAdd.push_back(c->otherPlayers[id]);
                playerLock.unlock();
            }
        }
        else if(!strcmp(cmd, CMD_PLAYER_LEAVE))
        {
            if(c->otherPlayers[uuid] != nullptr) c->otherPlayers[uuid]->connected = false;
            playerLock.lock();
            printf("[INFO] Player %d Left\n", uuid);
            playersToRemove.push_back(c->otherPlayers[uuid]);
            playerLock.unlock();
        }
        else if(!strcmp(cmd, CMD_ENTITY_SPAWN))
        {
            printBuffer(buffer, amount);
            int offset = 0;
            while(offset < amount)
            {
                int entityNum = read<int>(data);
                int entityID = read<int>(data);
                printf("[INFO] Entity with type: %d and id %d spawned\n", entityNum, entityID);
                
                
                Entity *e = Multiplayer::createEntityFromData((Multiplayer::MultiplayerEntities) entityNum, data);
                c->window->level->addEntity(e, entityID);
                data += Multiplayer::getEntitySize((Multiplayer::MultiplayerEntities) entityID) - 8;
                offset += Multiplayer::getEntitySize((Multiplayer::MultiplayerEntities) entityID);
            }
        }
        else if(!strcmp(cmd, CMD_ENTITY_MOVE))
        {
            int entityID = read<int>(data);
            Entity *e = c->window->level->getEntity(entityID);
            if(e == nullptr) continue; // Entity not found...
            e->data.x_pos = (float) read<int>(data);
            e->data.y_pos = (float) read<int>(data);
            
            if(dynamic_cast<Slime*>(e) != nullptr) ((Slime*) e)->anim = read<int>(data);
        }
        else if(!strcmp(cmd, CMD_BUILDING_ADD))
        {
            printf("Adding building...\n");
            c->window->level->buildings.push_back(new Building(read<int>(data), read<int>(data), read<uint16_t>(data), c->window->level));
        }
        else
        {
            printBuffer(buffer, 8);
            printf("Couldn't find command: %s\n", cmd);
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
    level->activePlayerLock.lock();
    for(int i = 0; i < (int) playersToAdd.size(); i++)
    {
        level->addEntity(playersToAdd[i]);
        level->activePlayers.push_back(playersToAdd[i]);
    }
    playersToAdd.clear();
    for(int i = 0; i < (int) playersToRemove.size(); i++)
    {
        level->removeEntity(playersToRemove[i]);
        for(int index = 0; index < level->activePlayers.size(); index++)
        {
            if(level->activePlayers[i] == playersToRemove[i])
            {
                level->activePlayers.erase(level->activePlayers.begin() + index);
                break;
            }
        }
    }
    playersToRemove.clear();
    playerLock.unlock();
    level->activePlayerLock.unlock();
}

void Multiplayer::Client::sendToServer(TCP_Packet packet)
{
    SDLNet_TCP_Send(tcp_socket, packet.data, packet.dataLen);
}

