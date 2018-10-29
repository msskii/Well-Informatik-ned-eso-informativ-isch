#include "Client.hpp"
#include "../graphics/Window.hpp"
#include "../level/loader/LevelLoader.hpp"
#include "ClientOverlay.hpp"
#include "ServerCommandHandlers.hpp"

std::mutex playerLock;
std::vector<Multiplayer::RemotePlayer*> playersToAdd;
std::vector<Multiplayer::RemotePlayer*> playersToRemove;

void Multiplayer::checkCommand(Multiplayer::Client *c, int amount, uint8_t* buffer, char *cmd, uint32_t uuid, uint8_t *data)
{
    // printf("[DEBUG] Executing cmd: %s\n", cmd);
    
    if(!strcmp(cmd, CMD_PLAYER_MOVE))
    {
        if(!c->otherPlayers[uuid] || !c->otherPlayers[uuid]->connected) return; // This player is not connected!?
        c->otherPlayers[uuid]->data.x_pos = (float) ((uint32_t*) (data))[0];
        c->otherPlayers[uuid]->data.y_pos = (float) ((uint32_t*) (data))[1];
        
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
            c->otherPlayers[id]->nameLen = read<uint32_t>(data);
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
    else if(!strcmp(cmd, CMD_PLAYER_CHAT))
    {
        c->clientoverlay->addMessage(std::string(readString(data)));
    }
    else if(!strcmp(cmd, CMD_ENTITY_SPAWN))
    {
        // printBuffer(buffer, amount);
        Entity *e = Multiplayer::deserializeEntity(data);
        c->sendToServer(createPacket(CMD_PACKET_RECEIVED, "", 0));
        
        if(!e) return; // Entity could not be deserialized
        c->window->level->addEntity(e, e->entityID);
    }
    else if(!strcmp(cmd, CMD_ENTITY_DIE))
    {
        int eid = Multiplayer::read<int>(data);
        c->window->level->entityLock.lock();
        c->window->level->serverRemoved.push_back(eid);
        c->window->level->entityLock.unlock();
    }
    else if(!strcmp(cmd, CMD_ENTITY_MOVE))
    {
        int entityID = read<int>(data);
        Entity *e = c->window->level->getEntity(entityID);
        if(e == nullptr) return; // Entity not found...
        e->data.x_pos = (float) read<int>(data);
        e->data.y_pos = (float) read<int>(data);
        
        if(dynamic_cast<Slime*>(e) != nullptr)
        {
            ((Slime*) e)->anim = read<int>(data);
        }
        
    }
    else if(!strcmp(cmd, CMD_LEVEL_INIT))
    {
        Loader::LevelLoader *loader = new Loader::LevelLoader(data); // uint8_t*!!!!
        c->window->level = loader->buildLevel();
        c->window->level->window = c->window;
        c->window->level->reloadFiles();
        c->window->level->clientConnector = c;
        c->window->level->remoteLevel = true; // We're still on the server
        printf("[INFO] Loaded level... You should see buildings now\n");
        c->sendToServer(createPacket(CMD_PACKET_RECEIVED, "", 0)); // Send empty ack
        // No consumed data (Comes from big packet service)
    }
    else if(!strcmp(cmd, CMD_SETUP_COMPLETE))
    {
        c->window->establishingConnection = false;
    }
    else if(!strcmp(cmd, CMD_PACKET_RECEIVED))
    {
        c->timeout = false;
    }
    else
    {
        printBuffer(buffer, 16);
        printf("[WARN] Couldn't find command: %s\n", cmd);
    }
}

int Multiplayer::clientReceive(void *data)
{
	Multiplayer::Client* c = (Multiplayer::Client*) data;

    char *cmd = (char*) malloc(3);
    cmd[2] = 0;
	uint8_t *buffer = new uint8_t[BUFFER_SIZE + 1];
	while (true)
	{
		int amount = SDLNet_TCP_Recv(c->tcp_socket, buffer, BUFFER_SIZE);
        int consumed = 0;
        
        if (amount <= 0)
		{
			// Some error occured, exit
			printf("[ERROR] Connection to server lost!\n");
			exit(0);
		}
        
        while(memcmp(buffer + amount - 4, FOOTER, 4)) // As long as it is not the end, receive more
        {
            if(BUFFER_SIZE - amount <= 0)
            {
                printf("[WARN] More buffer than you can handle\n");
                break;
            }
            amount += SDLNet_TCP_Recv(c->tcp_socket, buffer + amount, BUFFER_SIZE - amount);
        }
        
        buffer[amount] = 0;

        while(consumed < amount)
        {
            while(memcmp(buffer + consumed, HEADER, 4))
            {
                if(++consumed >= BUFFER_SIZE) break; // Wait for header
            }
            if(memcmp(buffer + consumed, HEADER, 4)) break;
            
            int len = consumed;
            while(memcmp(buffer + consumed, FOOTER, 4))
            {
                if(++consumed >= BUFFER_SIZE)
                {
                    memmove(buffer, buffer + len, consumed - len);
                    len = 0;
                    consumed = consumed - len;
                    if(consumed >= BUFFER_SIZE)
                    {
                        printf("[WARN] You are using more buffer space than you have!!!!\n");
                        break;
                    }
                    SDLNet_TCP_Recv(c->tcp_socket, buffer + consumed, BUFFER_SIZE - consumed);
                }
            }
            if(memcmp(buffer + consumed, FOOTER, 4)) break;
            
            len = consumed - len - 4; // difference between currently consumed and consumed at the header
            consumed -= len;
            
            int c1 = consumed;
            buffer += c1;
            uint32_t uuid = *((uint32_t*)buffer);
            cmd[0] = buffer[4];
            cmd[1] = buffer[5];
            uint8_t *data = buffer + 6; // 4 for uuid + 2 for cmd
            
            // checkCommand(c, BUFFER_SIZE - amount + consumed + len, buffer, cmd, uuid, data);
            checkCommand(c, len, buffer, cmd, uuid, data);

            buffer -= c1;
            consumed += len;
        }
	}

	return 0;
}

Multiplayer::Client::Client(Window *w, const char *address, std::string name)
{
    // Setup
    window = w;
	SDLNet_Init();

    // Connect to specified server
	IPaddress ip;
	SDLNet_ResolveHost(&ip, address, SERVER_PORT);
	tcp_socket = SDLNet_TCP_Open(&ip); // Connect to server...
    
    // No connection could be established
	if (tcp_socket == NULL)
	{
		printf("[ERROR] Couldn't connect to the server '%s' (SDLnet error: %s)\n", address, SDLNet_GetError());
        return;
	}
    
    // Add server to socket list
    SDLNet_TCP_AddSocket(sockets, tcp_socket);

    // We are connected!
    w->establishingConnection = true; // Server is not yet done with the setup
    connectionEstablished = true;
    
    // Send join message
	uint8_t *welcome = new uint8_t[6] { 0x41, 0x46 }; // Send welcoming message? --> Like name or stuff
    *((uint32_t*) (welcome + 2)) = (uint32_t) name.size();
    sendToServer(createPacket(CMD_PLAYER_JOIN, (char*) welcome, HEADER_SIZE));
    sendToServer(createPacket(CMD_PLAYER_NAME, name.c_str(), (int) name.size()));
    
    clientoverlay = new ClientOverlay();
    w->openMenu(clientoverlay);

    // Start receiver of the client
	SDL_CreateThread(clientReceive, "ClientReceiverTCP", this);
}

// Send the position updates of this player
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

// Add a new remote player
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
        for(uint32_t index = 0; index < level->activePlayers.size(); index++)
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

// Wrapper for a sender
void Multiplayer::Client::sendToServer(TCP_Packet packet)
{
    SDLNet_TCP_Send(tcp_socket, packet.data, packet.dataLen);
}

