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
    
    EventData eventData;
    eventData.event_x = TILE_SIZE * 6;
    eventData.event_y = TILE_SIZE * 1;
    eventData.event_w = TILE_SIZE / 2;
    eventData.event_h = TILE_SIZE;
    eventData.event_action = MOVE_PLAYER;
    eventData.event_type_filter = STEP_ON;
    eventData.triggerAmount = 0; // As many times triggered as you want
    eventData.event_id_dependency = 0; // No Event needs to be triggered first
    eventData.event_id = 0; // Auto increment & start from one

    events.push_back(new Event(eventData, new uint8_t[2] { RIGHT, 4 * TILE_SIZE })); // Move player 2 down
    
    eventData.event_x += TILE_SIZE * 4;
    eventData.triggerAmount = 1; // Triggered once
    eventData.event_id_dependency = 1;
    eventData.event_type_filter = PLAYER_INTERACT;
    events.push_back(new Event(eventData, new uint8_t[2] { LEFT, 4 * TILE_SIZE })); // Move player 2 down
    
    player->updateMovement(0, 0); // Update player before level loads
}

void Level::addEntity(Entity *e)
{
    e->addedToLevel(this);
    entities.push_back(e);
}

int Level::getEventSize()
{
    int es = 0;
    for(int i = 0; i < (int) events.size(); i++)
    {
        if(!events[i]->isStored) continue;
        es += 4 + sizeof(EventData);
        es += NUM_ARGS[events[i]->event_data.event_action];
    }
    return es;
}

int Level::getLevelSize()
{
    return 8 + width * height * sizeof(TileData) + 12 + (int) strlen(audioFile) + (int) strlen(tileMapFile) + (int) strlen(textFile);
}

void Level::render(SDL_Renderer *renderer) // and update
{
    int xoffset = player->getOffsetX();
    int yoffset = player->getOffsetY();
        
    for(int i = 0; i < (int) (width * height); i++)
    {
        tiles[i].render(renderer, xoffset + PLAYER_OFFSET_X, yoffset + PLAYER_OFFSET_Y);
    }
    
    for(int i = 0; i < (int) entities.size(); i++)
    {
        entities[i]->render(renderer, xoffset, yoffset);
    }
    
    // Events wont be rendered in the end
    for(int i = 0; i < (int) events.size(); i++)
    {
        events[i]->render(renderer, xoffset, yoffset);
    }
    
    player->render(renderer, xoffset, yoffset);
}

void Level::update()
{
    // Update events & (soon) entities
    
    for(int i = 0; i < (int) events.size(); i++)
    {
        if(events[i]->event_data.event_type_filter == ALL_EVENTS || events[i]->event_data.event_type_filter == GAME_LOOP) events[i]->trigger(events[i], GAME_LOOP, this, events[i]->arguments);

        if(events[i]->event_data.event_x + events[i]->event_data.event_w > player->x_pos && events[i]->event_data.event_x < player->x_pos + PLAYER_WIDTH && events[i]->event_data.event_y + events[i]->event_data.event_h > player->y_pos && events[i]->event_data.event_y < player->y_pos + PLAYER_HEIGHT)
        {
            // Player inside event
            if(events[i]->event_data.event_type_filter == ALL_EVENTS || events[i]->event_data.event_type_filter == STEP_ON) events[i]->trigger(events[i], STEP_ON, this, events[i]->arguments);
                        
            if(player->actionPressed)
            {
                if(events[i]->event_data.event_type_filter == ALL_EVENTS || events[i]->event_data.event_type_filter == PLAYER_INTERACT) events[i]->trigger(events[i], PLAYER_INTERACT, this, events[i]->arguments);
            }
        }
    }
    
    for(int i = 0; i < (int) entities.size(); i++) entities[i]->update(window->keyStates);
}

void Level::reloadFiles()
{
    text = TextLoader(textFile);
}

Tile Level::getTile(int screenX, int screenY)
{
    return tiles[screenX + width * screenY];
}
