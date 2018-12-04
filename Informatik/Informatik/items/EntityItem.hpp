//
//  EntityItem.hpp
//  Informatik
//
//  Created by Aaron Hodel on 05.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef EntityItem_hpp
#define EntityItem_hpp

#include "Item.hpp"
#include "../entity/Entity.hpp"

class EntityItem : public Entity
{
private:
    float vx = 0;
    float vy = 0;
    float initY;
    
public:
    //create a still lying item
    EntityItem(float x, float y, const char *id);
    //creat a item with initial velocity
    EntityItem(float x, float y, const char *id, float vx, float vy);

    Item *item = nullptr; // The item this thing holds in the level
    
    void pickUp();
    
    void initItem(float x, float y, const char *id);
    
    void onAddToLevel(Level *level) override;
    void render(int xoff, int yoff) override;
    void update(const uint8_t *keys) override;
    
    uint32_t getEntitySize() override;
    uint8_t *getSerializedEntity(uint8_t *buffer) override;
};

#endif /* EntityItem_hpp */
