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

class Level
{
private:
public:
    Player *player; // The player in this level
    uint32_t width, height; // 4 byte integers --> normal ints on most platforms
    std::vector<Event> events; // The events in this level
    Tile *tiles; // The tiles
    
    const char* audioFile = "default.wav";
    const char* tileMapFile = "default.tilemap";
    const char* textFile = "test.text";
    
    TextLoader text = TextLoader(textFile);

public:
    Tile getTile(int xcoord, int ycoord);
    
    Level(int w, int h);
    
    void reloadFiles();
    
    inline int getLevelSize() { return 8 + width * height * sizeof(SerializedTile) + 12 + (int) strlen(audioFile) + (int) strlen(tileMapFile) + (int) strlen(textFile); }
    inline int getEventSize()
    {
        int es = 4 + (int) events.size() * sizeof(SerializedEvent);
        for(int i = 0; i < (int) events.size(); i++) es += NUM_ARGS[events[i].toStore.event_action];
        return es;
    }
    
    void update();
    void render(SDL_Renderer *renderer);
};

#endif /* Level_hpp */
