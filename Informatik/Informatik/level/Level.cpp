//
//  Level.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Level.hpp"
#include "loader/EventActions.hpp"
#include "loader/LevelLoader.hpp"
#include "../multiplayer/Server.hpp"

Level::Level(int w, int h) : width(w), height(h), player(new Player(this)) // Number of tiles
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
    
    for (int i = 0; i < 10; i++)
    {
        tiles[50 * 15 + 10 +i].data.tileNumber = 0;
        tiles[50 * 14 + 10 +i].data.tileNumber = 0;
    }
    

    buildings.push_back(new Building(10, 10, 0, this));
    buildings.push_back(new Building(10, 20, 1, this));

    for(int i = 0; i < w * h; i++)
    {
        tiles[i].data.variant = rand() % 100 <= 2 ? 1 : rand() % 100 <= 2 ? 2 : 0; // Add stuff to the level
        tiles[i].reloadTexture(); // Load initial texture...
    }

    // Create texture
    srfc = SDL_CreateRGBSurfaceWithFormat(0, TILE_SIZE * width, TILE_SIZE * height, 32, SDL_PIXELFORMAT_ARGB8888);
    SDL_Rect dst = {0, 0, TILE_SIZE, TILE_SIZE};
    for(int i = 0; i < width * height; i++)
    {
        dst.x = tiles[i].xcoord * TILE_SIZE;
        dst.y = tiles[i].ycoord * TILE_SIZE;
        if(SDL_BlitScaled(tiles[i].Tile_surface, &tiles[i].Tile_surface->clip_rect, srfc, &dst))
        {
            printf("[ERROR] BlitSurface (level.cpp) error: %s\n", SDL_GetError());
        }
    }
    
    updateVariant(this); // Update all variants for the tiles
    
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
    
    eventData.event_x += TILE_SIZE * 4;
    eventData.event_id_dependency = 0;
    eventData.event_type_filter = STEP_ON;
    eventData.event_action = TELEPORT_PLAYER;
    events.push_back(new Event(eventData, new uint8_t[9] {0, 0, 0, 0, 0, 0, 0, 0, 1})); // two floats of zero & map id 1
    
    audioFile = std::string(GET_FILE_PATH(AUDIO_PATH, "default.wav"));
    printf("[DEBUG] AudioFile %s\n", audioFile.c_str());
    tileMapFile = std::string(GET_FILE_PATH(LEVEL_PATH, "default.tilemap"));
    textFile = std::string(GET_FILE_PATH(LEVEL_PATH, "test.text"));
    
    player->updateMovement(0, 0); // Update player before level loads
}

void Level::resetLevel()
{
    // Delete all data, for multiplayer
    entities.clear();
    buildings.clear();
    events.clear();
}

void Level::addEntity(Entity *e)
{
    addEntity(e, entityIDCounter++);
}

void Level::addEntity(Entity *e, int id)
{
    if(e == nullptr) return;
    if(typeid(*e) == typeid(NPC)) printf("Spawned NPC with id: %d\n", id);
    e->entityID = id;
    e->addedToLevel(this);
    entities.push_back(e);
    
    if(onServer)
    {
        // Send to clients
        
    }
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
    return 8 + width * height * sizeof(TileData) + 4 + sizeof(BuildingData) * (int) buildings.size() + 12 + (int) audioFile.size() + (int) tileMapFile.size() + (int) textFile.size();
}

void Level::render() // and update
{
    if(!level_texture.id) level_texture = getTexture(srfc);
    
    xoffset = player->getOffsetX();
    yoffset = player->getOffsetY();

    renderWithShading(level_texture, {-xoffset-PLAYER_OFFSET_X, -yoffset-PLAYER_OFFSET_Y, GAME_WIDTH, GAME_HEIGHT}, {0, 0, GAME_WIDTH, GAME_HEIGHT});
    
    //Check if Entities are behind a building, if yes render them here. Else set a flag to do so after the buildings
    
    //first set all to false
    for(int i = 0; i < (int) entities.size(); i++)
    {
        entities[i]->isBehind = false;
    }
    player->isBehind = false;
    
    //then check
    for(int j = 0; j < (int) buildings.size(); j++)
    {
        player->isBehind |= buildings[j]->isBehind(player->data.x_pos, player->data.y_pos);
        
        for(int i = 0; i < (int) entities.size(); i++)
        {
            entities[i]->isBehind |= buildings[j]->isBehind(entities[i]->data.x_pos, entities[i]->data.y_pos);
            if (entities[i]->isBehind)
            {
                entities[i]->render(xoffset, yoffset);
            }
        }
    }
    
    
    // Events wont be rendered in the end
    for(int i = 0; i < (int) events.size(); i++)
    {
        events[i]->render(xoffset, yoffset);
    }
    
    //render player if he is behind a building
    if (player->isBehind && !onServer) player->render(xoffset, yoffset);
    
    // Update & render other clients
    if (clientConnector != nullptr)
    {
        // We connected & arent playing singleplayer
        clientConnector->addRemotePlayers(this);
        clientConnector->updatePlayerPos((int) player->data.x_pos, (int) player->data.y_pos, player->animSet, player->anim, player->direction);
    }    
    
    //rendering Buildings
    for(int i = 0; i < (int) buildings.size(); i++)
    {
        buildings[i]->render(xoffset + PLAYER_OFFSET_X, yoffset + PLAYER_OFFSET_Y);
    }

    //Render player here if he is infront of building
    if (!player->isBehind && !onServer) player->render(xoffset, yoffset);
    
    //render entities here if they are infront of a building
    for(int i = 0; i < (int) entities.size(); i++)
    {
        if (!entities[i]->isBehind)
        {
            entities[i]->render(xoffset, yoffset);
        }
    }
}

void Level::update()
{
    if(remoteLevel && !onServer) return; // Don't update here, it's on the server

    for(int i = 0; i < (int) events.size(); i++)
    {
        if(events[i]->event_data.event_type_filter == ALL_EVENTS || events[i]->event_data.event_type_filter == GAME_LOOP) events[i]->trigger(GAME_LOOP, this);

        if(events[i]->event_data.event_x + events[i]->event_data.event_w > player->data.x_pos && events[i]->event_data.event_x < player->data.x_pos + PLAYER_WIDTH && events[i]->event_data.event_y + events[i]->event_data.event_h > player->data.y_pos && events[i]->event_data.event_y < player->data.y_pos + PLAYER_HEIGHT)
        {
            // Player inside event
            if(events[i]->event_data.event_type_filter == ALL_EVENTS || events[i]->event_data.event_type_filter == STEP_ON) events[i]->trigger(STEP_ON, this);
                        
            if(player->actionPressed)
            {
                if(events[i]->event_data.event_type_filter == ALL_EVENTS || events[i]->event_data.event_type_filter == PLAYER_INTERACT) events[i]->trigger(PLAYER_INTERACT, this);
            }
        }
    }
    
    uint8_t* data = (uint8_t*) malloc(3 * 10); // Just alloc too much
    for(int i = 0; i < (int) entities.size(); i++)
    {
        entities[i]->update(window->keyStates);
        if(onServer)
        {
            ((uint32_t*) data)[0] = entities[i]->entityID;
            ((uint32_t*) data)[1] = (int) entities[i]->data.x_pos;
            ((uint32_t*) data)[2] = (int) entities[i]->data.y_pos;
            Multiplayer::TCP_Packet packet;
            if(dynamic_cast<Slime*>(entities[i]) != nullptr)
            {
                ((uint32_t*) data)[3] = (int) ((Slime*) entities[i])->anim;
                packet = server->createServerPacket(CMD_ENTITY_MOVE, (char*) data, 4 * 4);
            }
            else
            {
                packet = server->createServerPacket(CMD_ENTITY_MOVE, (char*) data, 3 * 4);
            }
            server->sendToAll(packet);
            free(packet.data);
        }
    }
    free(data);
}

void Level::reloadFiles()
{
    text = new Loader::TextLoader(textFile.c_str());
}

Tile Level::getTile(int screenX, int screenY)
{
    return tiles[screenX + width * screenY];
}

bool Level::getBuildingCollision(float x, float y)
{
    for (int i = 0; i < (int) buildings.size(); i++)
    {
        if(buildings[i]->isInside(x, y))
        {
            return true;
        }
    }
    return false;
}

void Level::updateTile(int tilenum)
{
    printf("Updating tile at %d\n", tilenum);
    SDL_Rect dst = {tiles[tilenum].xcoord * TILE_SIZE, tiles[tilenum].ycoord * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    SDL_BlitScaled(tiles[tilenum].Tile_surface, &tiles[tilenum].Tile_surface->clip_rect, srfc, &dst);
    deleteTexture(level_texture);
    level_texture = getTexture(srfc);
}

void Level::updateTiles()
{
    deleteTexture(level_texture);
    SDL_Rect dst = {0, 0, TILE_SIZE, TILE_SIZE};
    for(int i = 0; i < width * height; i++)
    {
        dst.x = tiles[i].xcoord * TILE_SIZE;
        dst.y = tiles[i].ycoord * TILE_SIZE;
        if(SDL_BlitScaled(tiles[i].Tile_surface, &tiles[i].Tile_surface->clip_rect, srfc, &dst))
        {
            printf("[ERROR] BlitSurface (level.cpp) error: %s\n", SDL_GetError());
        }
    }
    level_texture.id = 0;
}

void Level::setLevelMap(uint8_t map)
{
    Level *nl = Loader::loadLevel(GET_FILE_PATH(LEVEL_PATH, "level_" + std::to_string(map) + ".level"), 50, 50);
    
    Loader::LevelLoader loader(window->level);
    loader.saveFile(window->level->levelFile.c_str());
    
    delete[] tiles;
    delete text;
    
    // Copy data from nl
    tiles = nl->tiles;
    events = nl->events;
    entities = nl->entities;
    width = nl->width;
    height = nl->height;
    buildings = nl->buildings;
    
    levelFile = nl->levelFile;
    audioFile = nl->audioFile;
    tileMapFile = nl->tileMapFile;
    textFile = nl->textFile;
    text = nl->text;
}
