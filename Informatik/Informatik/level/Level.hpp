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

#include "../enemy/pathfinding/PathFinder.hpp"

class Player;
class Window;
class PathFinder;
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
    std::mutex entityLock; // Locks the entities because the server might interfere with them
    std::vector<Entity*> serverAdded; // The entites clients have spawned
    std::vector<int> serverRemoved; // The entities clients have removed
    
    std::vector<Entity*> entities; // The entities in the level
    PathFinder *pathfinder = nullptr;
    Tile *tiles; // The tiles
    std::vector<Building*> buildings;
    
    bool remoteLevel = false; // If the level is on a remote host (Server)
    bool onServer = false; // If this level is run on the server

    Multiplayer::Server *server = nullptr;
    Multiplayer::Client *clientConnector = nullptr;

    inline bool connectToServer(const char *address, std::string name)
    {
        clientConnector = new Multiplayer::Client(window, address, name);
        return clientConnector->connectionEstablished;
    }
    
    std::mutex activePlayerLock;
    std::vector<Multiplayer::RemotePlayer*> activePlayers;
    Player *getPlayer(float xcoord, float ycoord);
    
    void resetLevel();
    inline Player *getLocalPlayer() { return player; }
    
    inline int getOffsetX() { return player->getOffsetX(); }
    inline int getOffsetY() { return player->getOffsetY(); }

    float sunBrightness = 0.4f;

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
    std::vector<Entity*> findEntities(float x, float y, float radius); // Finds close enemies
    
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
