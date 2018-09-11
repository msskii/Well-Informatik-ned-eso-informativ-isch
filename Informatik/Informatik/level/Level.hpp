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

#include "../entity/Player.hpp"

#include "loader/TextLoader.hpp"

#ifdef ENABLE_TEST_MULTIPLAYER
#  include "../multiplayer/Client.hpp"
#endif

class Player;
class Window;

class Level
{
private:
public:
    Player *player; // The player in this level
    uint32_t width, height; // 4 byte integers --> normal ints on most platforms
    std::vector<Event*> events; // The events in this level
    std::vector<Entity*> entities; // The entities in the level
    Tile *tiles; // The tiles

#ifdef ENABLE_TEST_MULTIPLAYER
	Multiplayer::Client *clientConnector = nullptr;
	inline void connectToServer(const char *address) { clientConnector = new Multiplayer::Client(address);  }
#endif
    
    int xoffset, yoffset;
    
    std::string audioFile = GET_FILE_PATH(AUDIO_PATH, "default.wav");
    std::string tileMapFile = GET_FILE_PATH(LEVEL_PATH, "default.tilemap");
    std::string textFile = GET_FILE_PATH(LEVEL_PATH, "test.text");
    
    Loader::TextLoader *text;
    Window *window = nullptr;
public:
    Tile getTile(int xcoord, int ycoord);
    
    Level(int w, int h, SDL_Renderer *renderer);
    Level(int w, int h);
    
    void reloadFiles();
    void addEntity(Entity *e); // To add an entity
    void removeEntity(Entity *e);
    
    int getLevelSize();
    int getEventSize();
    
    void update();
    void render(SDL_Renderer *renderer);
};

#include "../graphics/Window.hpp"

#endif /* Level_hpp */
