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
#include <vector>

#include "Tile.hpp"
#include "Event.hpp"
#include "Building.hpp"

#include "../entity/Player.hpp"

#include "loader/TextLoader.hpp"

#include "../multiplayer/Client.hpp"

class Player;
class Window;

class Level
{
private:
    SDL_Surface *srfc;
    Player *player; // The player in this level
    
public:
    uint32_t width, height; // 4 byte integers --> normal ints on most platforms
    std::vector<Event*> events; // The events in this level
    std::vector<Entity*> entities; // The entities in the level
    Tile *tiles; // The tiles
    Building *buildings; //The Buildings .. you guessed
    
    bool remoteLevel = false;
    bool onServer = false;
    Multiplayer::Client *clientConnector = nullptr;
    inline bool connectToServer(const char *address, std::string name)
    {
        clientConnector = new Multiplayer::Client(window, address, name);
        return clientConnector->connectionEstablished;
    }
    
    std::vector<Multiplayer::RemotePlayer*> activePlayers;
    inline Player *getPlayer(float xcoord, float ycoord)
    {
        if(!remoteLevel) return player;
        else if(onServer) return nullptr; // TODO: find closest player
        return player;
    }
    
    inline Player *getLocalPlayer() { return player; }
    
    inline int getOffsetX() { return player->getOffsetX(); }
    inline int getOffsetY() { return player->getOffsetY(); }

    float sunBrightness = 0.6f;
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
    int buildingCount = 2;
    
    Tile getTile(int xcoord, int ycoord);
    bool getBuildingCollision(float x, float y);
    
    //Level(int w, int h, SDL_Renderer *renderer);
    Level(int w, int h);
    void updateTile(int tilenum);
    void updateTiles();

    void reloadFiles();
    void addEntity(Entity *e); // To add an entity
    void removeEntity(Entity *e);
    
    int getLevelSize();
    int getEventSize();
    
    void update();
    void render();
};

#include "../graphics/Window.hpp"

#endif /* Level_hpp */
