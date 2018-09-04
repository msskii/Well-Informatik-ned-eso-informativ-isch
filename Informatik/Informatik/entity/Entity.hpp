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
    
    float maxhealth = 0;
    float currentHealth = 0;
} EntityData;

class Entity
{
protected:
    
public:
    Level *level;
    
    EntityData data;
    void addedToLevel(Level *level);
    
    virtual void onAddToLevel(Level *level) = 0;
    
    virtual void render(SDL_Renderer *renderer, int xoff, int yoff) = 0;
    virtual void update(const uint8_t *keys) = 0;
};

#endif /* Entity_hpp */
