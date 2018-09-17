//
//  Level.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Level.hpp"
#include "loader/EventActions.hpp"


Level::Level(int w, int h) : width(w), height(h), player(new Player(this))
{
    tiles = new Tile[w * h];
    buildings = new Building[1];
    player->updateMovement(0, 0); // Update player before level loads
}

Level::Level(int w, int h, SDL_Renderer *renderer) : width(w), height(h), player(new Player(this)) // Number of tiles
{
    tiles = new Tile[w * h];
    
    for(int i = 0; i < w * h; i++)
    {
        if (i % 50 == 3) 
		{
            tiles[i] = Tile(i % w, i / w, 1);
        }
		else if (i % 50 == 5 || i % 50 == 6)
        {
            tiles[i] = Tile(i % w, i / w, 0);
        }
		else
        {
            tiles[i] = Tile(i % w, i / w, 2);
        }
    }
    tiles[230].data.tileNumber = 0;
    tiles[229].data.tileNumber = 0;
    tiles[231].data.tileNumber = 0;
    tiles[179].data.tileNumber = 0;
    tiles[180].data.tileNumber = 0;
    tiles[181].data.tileNumber = 0;
    tiles[280].data.tileNumber = 0;
    tiles[281].data.tileNumber = 0;
    tiles[279].data.tileNumber = 0;
    
    
    tiles[240].data.tileNumber = 0;
    tiles[290].data.tileNumber = 0;
    tiles[340].data.tileNumber = 0;
    tiles[440].data.tileNumber = 0;
    tiles[441].data.tileNumber = 0;
    tiles[439].data.tileNumber = 0;
    tiles[540].data.tileNumber = 0;
    
    for (int i = 0; i < 10; i++) {
        tiles[50 * 15 + 10 +i].data.tileNumber = 0;
        tiles[50 * 14 + 10 +i].data.tileNumber = 0;
    }
    
    
    buildings = new Building[1]
    {
        Building(10, 10, 0)
    };

    
    
    
    
    

  //  for(int i = 0; i < w * h; i++) tiles[i] = Tile(i % w, i / w, 0); // default to tile number 0
    
    for(int i = 0; i < w * h; i++) tiles[i].data.variant = rand() % 100 <= 2 ? 1 : rand() % 100 <= 2 ? 2 : 0; // Add stuff to the level
    
    updateVariant(this, renderer); // Update all variants for the tiles
    for(int i = 0; i < w * h; i++) tiles[i].reloadTexture(renderer);
    
    textFile = GET_FILE_PATH(LEVEL_PATH, "test.text"); // Somehow this wasnt initialized on windows but on mac it was...
	text = new Loader::TextLoader(textFile.c_str());
    
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

    events.push_back(new Event(eventData, new uint8_t[2] { DOWN, 3 * TILE_SIZE })); // Move player 2 down
    
    eventData.event_x += TILE_SIZE * 4;
    eventData.triggerAmount = 1; // Triggered once
    eventData.event_id_dependency = 1;
    eventData.event_type_filter = PLAYER_INTERACT;
    events.push_back(new Event(eventData, new uint8_t[2] { UP, 3 * TILE_SIZE })); // Move player 2 down
    
    audioFile = std::string(GET_FILE_PATH(AUDIO_PATH, "default.wav"));
    printf("AudioFile %s\n", audioFile.c_str());
    tileMapFile = std::string(GET_FILE_PATH(LEVEL_PATH, "default.tilemap"));
    textFile = std::string(GET_FILE_PATH(LEVEL_PATH, "test.text"));
    
    player->updateMovement(0, 0); // Update player before level loads
}

void Level::addEntity(Entity *e)
{
    e->addedToLevel(this);
    entities.push_back(e);
}

void Level::removeEntity(Entity *e)
{
    for(int i = 0; i < (int) entities.size(); i++) if(entities[i] == e) entities.erase(entities.begin() + i);
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
    return 8 + width * height * sizeof(TileData) + 12 + (int) audioFile.size() + (int) tileMapFile.size() + (int) textFile.size();
}

void Level::render(SDL_Renderer *renderer) // and update
{
    xoffset = player->getOffsetX();
    yoffset = player->getOffsetY();
    
    //Render all Tiles
    for(int i = 0; i < (int) (width * height); i++)
    {
        tiles[i].render(renderer, xoffset + PLAYER_OFFSET_X, yoffset + PLAYER_OFFSET_Y);
    }
    
    //Check if Enteties are behind a building, if yes render them here. Else set a flag to do so after the buildings
    for(int i = 0; i < (int) entities.size(); i++)
    {
        for(int i = 0; i < buildingCount; i++)
        {
            buildings[i].isBehind(entities[i]->data.x_pos, entities[i]->data.y_pos) ? entities[i]->isBehind = true : entities[i]->isBehind = false;
            buildings[i].isBehind(player->x_pos, player->y_pos) ? player->isBehind = true : player->isBehind = false;
            
        }
        if (entities[i]->isBehind == true) {
            entities[i]->render(renderer, xoffset, yoffset);
        }
        
    }
    
    // Events wont be rendered in the end
    for(int i = 0; i < (int) events.size(); i++)
    {
        events[i]->render(renderer, xoffset, yoffset);
    }
    
    //render player if he is behind a building
    if (player->isBehind == true)   player->render(renderer, xoffset, yoffset);
    

    
#ifdef ENABLE_TEST_MULTIPLAYER
	if (clientConnector != nullptr)
	{
		// We connected & arent playing singleplayer
		clientConnector->render(renderer, xoffset, yoffset);
		clientConnector->updatePlayerPos((int) player->x_pos, (int) player->y_pos);
	}
#endif
    //rendering Buildings
    for(int i = 0; i < buildingCount; i++)
    {
        buildings[i].render(renderer, xoffset + PLAYER_OFFSET_X, yoffset + PLAYER_OFFSET_Y);
    }

    //Render player here if he is infront of building
    if (player->isBehind == false)  player->render(renderer, xoffset, yoffset);
    
    //render enteties here if they are infrong of a building
    for(int i = 0; i < (int) entities.size(); i++)
    {
        if (entities[i]->isBehind == false) {
            entities[i]->render(renderer, xoffset, yoffset);
        }
        
    }
}

void Level::update()
{
    // Update events & (soon) entities
    
    for(int i = 0; i < (int) events.size(); i++)
    {
        if(events[i]->event_data.event_type_filter == ALL_EVENTS || events[i]->event_data.event_type_filter == GAME_LOOP) events[i]->trigger(GAME_LOOP, this);

        if(events[i]->event_data.event_x + events[i]->event_data.event_w > player->x_pos && events[i]->event_data.event_x < player->x_pos + PLAYER_WIDTH && events[i]->event_data.event_y + events[i]->event_data.event_h > player->y_pos && events[i]->event_data.event_y < player->y_pos + PLAYER_HEIGHT)
        {
            // Player inside event
            if(events[i]->event_data.event_type_filter == ALL_EVENTS || events[i]->event_data.event_type_filter == STEP_ON) events[i]->trigger(STEP_ON, this);
                        
            if(player->actionPressed)
            {
                if(events[i]->event_data.event_type_filter == ALL_EVENTS || events[i]->event_data.event_type_filter == PLAYER_INTERACT) events[i]->trigger(PLAYER_INTERACT, this);
            }
        }
    }
    
    for(int i = 0; i < (int) entities.size(); i++) entities[i]->update(window->keyStates);
}

void Level::reloadFiles()
{
    text = new Loader::TextLoader(textFile.c_str());
}

Tile Level::getTile(int screenX, int screenY)
{
    return tiles[screenX + width * screenY];
}

bool Level::getBuildingCollision(float x, float y){
    
    for (int i = 0; i < buildingCount; i++)
    {
        if(buildings[i].isInside(x,y))
        {
            return true;
        }
    }
    return false;
}
