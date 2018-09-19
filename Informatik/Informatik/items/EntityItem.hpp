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
    
public:
    EntityItem(int x, int y, Item *item);
    
    Item *item = nullptr; // The item this thing holds in the level
    
    void pickUp();
    
    void onAddToLevel(Level *level) override;
    void render(int xoff, int yoff) override;
    void update(const uint8_t *keys) override;
};

#endif /* EntityItem_hpp */
