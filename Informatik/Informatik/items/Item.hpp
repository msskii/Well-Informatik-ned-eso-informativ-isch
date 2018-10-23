//
//  Item.hpp
//  Informatik
//
//  Created by Aaron Hodel on 05.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Item_hpp
#define Item_hpp

#include "../util/SDL_Util.hpp"

class Item
{
public:
    const char* name = nullptr;

public:
    SDL_Surface *surface = nullptr;
    gl_texture texture;
    
    inline bool operator==(Item *other) { return other == nullptr ? false : strcmp(name, other->name) == 0; };
    
    Item(const char* itemname);
};

typedef struct InventoryElement
{
    Item *item = nullptr;
    int numSlot = 0;
    int amountItems = 0;
} InventoryElement;

#endif /* Item_hpp */
