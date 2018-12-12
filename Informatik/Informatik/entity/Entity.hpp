//
//  Entity.hpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include "../util/SDL_Util.hpp"
#include "../level/Tile.hpp"
#include "../config.h"

enum DIRECTION
{
    DOWN = 0,
    UP,
    LEFT,
    RIGHT
};

#pragma pack(push, 1)
typedef struct EntityData
{
    float x_pos = 0;
    float y_pos = 0;
    uint8_t z_pos = 0;
    int ID = 0;
    
    float width = TILE_SIZE;
    float height = TILE_SIZE;
    
    float maxhealth = 10;
    float currentHealth = 10;
    float damage = 0;
    
    float dx = 0;
    float dy = 0;
    float speed = 0;
    
    int animFrames = 0;
    int animeSpeed = 0;
} EntityData;
#pragma pack(pop)

#define ABOVE_BUILDING  0x0
#define BEHIND_BUILDING 0x1
#define RENDERED        0x2

class Entity
{
protected:
    
public:
    //animation stuff
    int anim = 0, set = 0, timer = 0;
    
    int isBehind = ABOVE_BUILDING;
    Level *level;
    int entityID;
    
    ~Entity();
    
    EntityData data;
    void addedToLevel(Level *level);
    bool isInside(float dx, float dy);
    void correctMovement(float &dx, float &dy);
    
    inline SDL_Rect getBoundingBox() { return {(int) data.x_pos, (int) data.y_pos, (int) data.width, (int) data.height}; }
    
    virtual uint32_t getEntitySize(); // Calculate the size of the entity in bytes
    virtual uint8_t *getSerializedEntity(uint8_t* buffer); // Serialize the entity to send it to the server
    
    virtual void onAddToLevel(Level *level) = 0;
    
    virtual void render(int xoff, int yoff) = 0;
    virtual void update(const uint8_t *keys) = 0;
    //virtual bool collision(float x, float y) = 0;
};

// Some pythagoras
#define ENTITY_DIST(e1, e2) LENGTH(e1->data.x_pos - e2->data.x_pos, e1->data.y_pos - e2->data.y_pos)
#define PLAYER_DIST(e1, p) LENGTH(e1->data.x_pos - p->data.x_pos, e1->data.y_pos - p->data.y_pos)
#define ENTITY_DIAGONAL(e) LENGTH(e->data.width, e->data.height)

#endif /* Entity_hpp */
