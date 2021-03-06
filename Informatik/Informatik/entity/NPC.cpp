//
//  NPC.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 27.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "NPC.hpp"
#include "../level/Level.hpp"
#include "../multiplayer/Buffer.hpp"

NPC::NPC(uint8_t *serialized)
{
    data = Multiplayer::read<EntityData>(serialized);
    int len = Multiplayer::read<uint32_t>(serialized);
    for(int i = 0; i < len; i++)
    {
        NPCText nt;
        nt.timesDisplayed = Multiplayer::read<uint32_t>(serialized);
        nt.eventTriggered = Multiplayer::read<uint32_t>(serialized);
        nt.text = Multiplayer::readString(serialized);
        texts.push_back(nt);
    }
    animation = Multiplayer::read<NPCAnimation>(serialized);
    
    printf("[INFO] Created new NPC from serialized data at %.8f %.8f\n", data.x_pos, data.y_pos);

    setTexture();
    
    createEvent();
}

NPC::NPC(float xPos, float yPos, int ID, int level)
{
    printf("[INFO] Created new NPC at %.8f %.8f\n", xPos, yPos);
    
    data.x_pos = xPos;
    data.y_pos = yPos;
    data.ID = ID;
    data.height = 2 * TILE_SIZE;
    data.width = TILE_SIZE;
    
    setTexture();
    
    createEvent();
}

void NPC::createEvent()
{
    EventData evt;
    evt.event_x = (int)(data.x_pos);
    evt.event_y = (int)(data.y_pos);
    evt.event_w = (int) data.width;
    evt.event_h = (int) data.height;
    
    evt.event_id_dependency = 0; // No dependency
    evt.triggerAmount = 0; // Infinite amounts
    
    evt.event_type_filter = PLAYER_INTERACT;
    evt.event_action = NPC_INTERACT;
    evt.event_id = 0;
    
    event = new Event(evt, (uint8_t*) this);
    event->isStored = false; // Don't store it in the level file
}

uint32_t NPC::getEntitySize()
{
    int textsize = 4; // Amount of texts
    for(uint32_t i = 0; i < texts.size(); i++) textsize += 12 + strlen(texts[i].text);
    return sizeof(EntityData) + textsize + sizeof(NPCAnimation);
}

uint8_t *NPC::getSerializedEntity(uint8_t* buffer)
{
    Multiplayer::write<EntityData>(buffer, data);
    Multiplayer::write<uint32_t>(buffer, (uint32_t) texts.size());
    for(uint32_t i = 0; i < texts.size(); i++)
    {
        Multiplayer::write<uint32_t>(buffer, texts[i].timesDisplayed);
        Multiplayer::write<uint32_t>(buffer, texts[i].eventTriggered);
        Multiplayer::writeString(buffer, texts[i].text, (uint32_t) strlen(texts[i].text));
    }
    Multiplayer::write<NPCAnimation>(buffer, animation);
    return buffer;
}


void NPC::onInteractWith()
{
    bool isFacingMe = false;
    
    Player *player = level->getPlayer(data.x_pos, data.y_pos);
    
    isFacingMe |= player->data.x_pos + PLAYER_WIDTH / 2 < data.x_pos + data.width / 2 && player->direction == RIGHT;
    isFacingMe |= player->data.x_pos + PLAYER_WIDTH / 2 > data.x_pos + data.width / 2  && player->direction == LEFT;
    isFacingMe |= player->data.y_pos + PLAYER_HEIGHT / 2 < data.y_pos + data.height / 2 + data.height && player->direction == DOWN;
    isFacingMe |= player->data.y_pos + PLAYER_HEIGHT / 2 > data.y_pos + data.height / 2 && player->direction == UP;

    if(isFacingMe && currentText < (int) texts.size() && level->getLocalPlayer()->inControl)
    {
        NPCText text = texts[currentText];
        level->window->openMenu(new DialogOverlay(text.text));
        level->getLocalPlayer()->inControl = false;
        
        if(text.eventTriggered > 0)
        {
            for(int i = 0; i < (int) level->events.size(); i++)
            {
                if(text.eventTriggered == level->events[i]->event_data.event_id) level->events[i]->trigger(NPC_FINISHED_TALKING, level);
            }
        }
        
        if(++currentNumTriggered >= text.timesDisplayed && text.timesDisplayed > 0)
        {
            ++currentText;
            currentNumTriggered = 0;
        }
    }
}

void NPC::render(int xoff, int yoff)
{
    if(texture.id == 0) texture = getTexture(NPC_surface);
    
    SDL_Rect src = {32 * animation.anim, 0, (int) data.width / 2, (int) data.height / 2};
    SDL_Rect dst = {(int) data.x_pos, (int) data.y_pos, TILE_SIZE, 2 * TILE_SIZE};
    TRANSFORM_LEVEL_POS(dst, xoff, yoff);
    if(dst.x >= (GAME_WIDTH + TILE_SIZE) || dst.x < (-TILE_SIZE - TILE_SIZE) || dst.y >= (GAME_HEIGHT + 2 * TILE_SIZE) || dst.y < (-TILE_SIZE - 2 * TILE_SIZE)) return; // Only render the visible ones...
    renderWithShading(texture, src, dst);
    
}

void NPC::update(const uint8_t *keys)
{
    event->event_data.event_x = (int)(data.x_pos - PLAYER_WIDTH);
    event->event_data.event_y = (int)(data.y_pos - PLAYER_HEIGHT);
    
    if((animation.timer++) >= animation.timePerFrame)
    {
        animation.timer = 0;
        animation.anim = (animation.anim + 1) % animation.frameCount;
    }
}

void NPC::onAddToLevel(Level *l)
{
    level->events.push_back(event); // Add the event to the level
}

void NPC::setTexture(){
    switch (data.ID) {
        case 0:
            NPC_surface = IMG_Load(GET_TEXTURE_PATH("NPCs/OldMan"));
            animation.canWalk = false;
            animation.frameCount = 4;
            animation.timePerFrame = 20;
            break;
            
        default:
            break;
    }

}
