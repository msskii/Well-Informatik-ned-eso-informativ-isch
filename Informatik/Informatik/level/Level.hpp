//
//  Level.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Level_hpp
#define Level_hpp

#include "Tile.hpp"
#include "Event.hpp"
#include "../entity/Player.hpp"
#include <stdint.h>
#include <vector>
#include "loader/TextLoader.hpp"

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
    
    const char* audioFile = GET_FILE_PATH(AUDIO_PATH, "default.wav");
    const char* tileMapFile = GET_FILE_PATH(LEVEL_PATH, "default.tilemap");
    const char* textFile = GET_FILE_PATH(LEVEL_PATH, "test.text");
    
    TextLoader text = TextLoader(textFile);
    Window *window = nullptr;
public:
    Tile getTile(int xcoord, int ycoord);
    
    Level(int w, int h);
    
    void reloadFiles();
    void addEntity(Entity *e); // To add an entity
    
    int getLevelSize();
    int getEventSize();
    
    void update();
    void render(SDL_Renderer *renderer);
};

#include "../graphics/Window.hpp"

#endif /* Level_hpp */
