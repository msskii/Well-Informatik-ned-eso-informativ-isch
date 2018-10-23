//
//  Level.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Level_hpp
#define Level_hpp

#include <stdint.h>
#include <mutex>
#include <vector>

#include "Tile.hpp"
#include "Event.hpp"
#include "Building.hpp"
#include "../entity/decorativeEntities/Fireflies.hpp"

#include "../entity/Player.hpp"
#include "loader/TextLoader.hpp"
#include "../multiplayer/Client.hpp"

class Player;
class Window;
namespace Multiplayer
{
    class Server;
}

class Level
{
private:
    SDL_Surface *srfc;
    Player *player; // The player in this level
    int entityIDCounter = 0;
    
public:
    uint32_t width, height; // 4 byte integers --> normal ints on most platforms
    std::vector<Event*> events; // The events in this level
    std::vector<Entity*> entities; // The entities in the level
    Tile *tiles; // The tiles
    std::vector<Building*> buildings;
    
    bool remoteLevel = false;
    bool onServer = false;

    Multiplayer::Server *server = nullptr;
    Multiplayer::Client *clientConnector = nullptr;

    inline bool connectToServer(const char *address, std::string name)
    {
        clientConnector = new Multiplayer::Client(window, address, name);
        return clientConnector->connectionEstablished;
    }
    
    std::mutex activePlayerLock;
    std::vector<Multiplayer::RemotePlayer*> activePlayers;
    inline Player *getPlayer(float xcoord, float ycoord)
    {
        if(!remoteLevel) return player;
        else if(onServer)
        {
            Player *closest = nullptr;
            activePlayerLock.lock();
            for(int i = 0; i < (int) activePlayers.size(); i++)
            {
                if(closest == nullptr) closest = activePlayers[i];
                else if(LENGTH(xcoord - activePlayers[i]->data.x_pos, ycoord - activePlayers[i]->data.y_pos) < LENGTH(xcoord - closest->data.x_pos, ycoord - closest->data.y_pos)) closest = activePlayers[i];
            }
            activePlayerLock.unlock();
            return closest;
        }
        return player;
    }
    
    void resetLevel();
    inline Player *getLocalPlayer() { return player; }
    
    inline int getOffsetX() { return player->getOffsetX(); }
    inline int getOffsetY() { return player->getOffsetY(); }

    float sunBrightness = 0.5f;

    int xoffset, yoffset;
    void setLevelMap(uint8_t map);
    
    std::string levelFile = GET_FILE_PATH(LEVEL_PATH, "testlevel.level");
    std::string audioFile = GET_FILE_PATH(AUDIO_PATH, "default.wav");
    std::string tileMapFile = GET_FILE_PATH(LEVEL_PATH, "default.tilemap");
    std::string textFile = GET_FILE_PATH(LEVEL_PATH, "test.text");
    
    Loader::TextLoader *text;
    Window *window = nullptr;
    gl_texture level_texture; // All tiles in one texture?
    

public:    
    Tile getTile(int xcoord, int ycoord);
    bool getBuildingCollision(float x, float y);
    
    Level(int w, int h);
    void updateTile(int tilenum);
    void updateTiles();

    void reloadFiles();
    void addEntity(Entity *e); // To add an entity
    void addEntity(Entity *e, int id);
    void removeEntity(Entity *e);
    
    // Multiplayer stuff
    inline void setEntity(int id, Entity *e)
    {
        for(int i = 0; i < (int) entities.size(); i++) if(entities[i]->entityID == id) {entities[i] = e; return; }
        entities.push_back(e); // Not found, create it
    }
    
    inline Entity *getEntity(int id)
    {
        for(int i = 0; i < (int) entities.size(); i++) if(entities[i]->entityID == id) return entities[i];
        return nullptr;
    }
    
    // Saving stuff
    int getLevelSize();
    int getEventSize();
    
    // Game stuff
    void update();
    void render();
};

#include "../graphics/Window.hpp"

#endif /* Level_hpp */
