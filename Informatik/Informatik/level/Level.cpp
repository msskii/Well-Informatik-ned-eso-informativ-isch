//
//  Level.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Level.hpp"
#include "loader/EventActions.hpp"

Level::Level(int w, int h) : width(w), height(h), tiles(new Tile[w * h]), player(new Player(this)) // Number of tiles
{
    for(int i = 0; i < w * h; i++)
    {
        tiles[i] = Tile(i % w, i / w);
    }
    
    tiles[105].data.tileZ = 1;
    tiles[106].data.tileZ = 1;
    
    SerializedEvent eventData;
    eventData.event_x = TILE_SIZE * 6;
    eventData.event_y = TILE_SIZE * 1;
    eventData.event_w = TILE_SIZE / 2;
    eventData.event_h = TILE_SIZE;
    eventData.event_action = MOVE_PLAYER;
    eventData.event_type_filter = STEP_ON;
    eventData.triggerAmount = 0; // As many times triggered as you want
    eventData.event_id_dependency = 0; // No Event needs to be triggered first


    events.push_back(Event(eventData, new uint8_t[2] { RIGHT, 2 * TILE_SIZE })); // Move player 2 down
    
    eventData.event_x += TILE_SIZE * 2;
    eventData.triggerAmount = 1; // Triggered once
    eventData.event_type_filter = PLAYER_INTERACT;
    events.push_back(Event(eventData, new uint8_t[2] { LEFT, 2 * TILE_SIZE })); // Move player 2 down
}

void Level::render(SDL_Renderer *renderer) // and update
{
    int xoffset = -player->_x;
    int yoffset = -player->_y;
        
    for(int i = 0; i < width * height; i++)
    {
        tiles[i].render(renderer, xoffset + PLAYER_OFFSET_X, yoffset + PLAYER_OFFSET_Y);
    }
    
    for(int i = 0; i < events.size(); i++)
    {
        events[i].render(renderer, xoffset, yoffset);
    }
    
    player->render(renderer, xoffset, yoffset);
}

void Level::update()
{
    // Update events & (soon) entities
    
    for(int i = 0; i < events.size(); i++)
    {
        if(events[i].toStore.event_type_filter == ALL_EVENTS || events[i].toStore.event_type_filter == GAME_LOOP) events[i].trigger(events[i], GAME_LOOP, this, events[i].arguments);

        if(events[i].toStore.event_x + events[i].toStore.event_w > player->_x && events[i].toStore.event_x < player->_x + PLAYER_WIDTH && events[i].toStore.event_y + events[i].toStore.event_h > player->_y && events[i].toStore.event_y < player->_y + PLAYER_HEIGHT)
        {
            // Player inside event
            if(events[i].toStore.event_type_filter == ALL_EVENTS || events[i].toStore.event_type_filter == STEP_ON) events[i].trigger(events[i], STEP_ON, this, events[i].arguments);
            
            if(player->actionPressed)
            {
                if(events[i].toStore.event_type_filter == ALL_EVENTS || events[i].toStore.event_type_filter == PLAYER_INTERACT) events[i].trigger(events[i], PLAYER_INTERACT, this, events[i].arguments);
            }
        }
    }
}

Tile Level::getTile(int screenX, int screenY)
{
    return tiles[screenX + width * screenY];
}
