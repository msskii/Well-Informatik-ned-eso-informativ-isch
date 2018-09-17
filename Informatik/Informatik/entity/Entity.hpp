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

class Level;

enum DIRECTION
{
    DOWN = 0,
    UP,
    LEFT,
    RIGHT
};

typedef struct EntityData
{
    float x_pos = 0;
    float y_pos = 0;
    
    float width = TILE_SIZE;
    float height = TILE_SIZE;
    
    float maxhealth = 10;
    float currentHealth = 10;
    float damage = 0;
    
    float speed = 0;
} EntityData;

class Entity
{
protected:
    
public:
    bool isBehind = false;
    Level *level;
    
    ~Entity();
    
    EntityData data;
    void addedToLevel(Level *level);
    
    inline SDL_Rect getBoundingBox() { return {(int) data.x_pos, (int) data.y_pos, (int) data.width, (int) data.height}; }
    
    virtual void onAddToLevel(Level *level) = 0;
    
    virtual void render(SDL_Renderer *renderer, int xoff, int yoff) = 0;
    virtual void update(const uint8_t *keys) = 0;
};

#define ENTITY_DIST(e1, e2) LENGTH(e1->data.x_pos - e2->data.x_pos, e1->data.y_pos - e2->data.y_pos)
#define PLAYER_DIST(e1, p) LENGTH(e1->data.x_pos - p->x_pos, e1->data.y_pos - p->y_pos)
#define ENTITY_DIAGONAL(e) LENGTH(e->data.width, e->data.height)

#endif /* Entity_hpp */
