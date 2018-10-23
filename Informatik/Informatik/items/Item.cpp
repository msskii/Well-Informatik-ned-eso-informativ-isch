//
//  Item.cpp
//  Informatik
//
//  Created by Aaron Hodel on 05.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Item.hpp"

Item::Item(const char *itemname) : name(itemname)
{
    surface = IMG_Load(GET_TEXTURE_PATH("items/" + itemname));
    if(!surface) printf("[ERROR] Error loading item texture %s\n", itemname);
}
