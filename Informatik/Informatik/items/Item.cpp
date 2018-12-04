//
//  Item.cpp
//  Informatik
//
//  Created by Aaron Hodel on 05.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Item.hpp"
#include "../config/ConfigLoader.hpp"
#include "../config/Language.hpp"

Item::Item(const char *itemname) : name(itemname)
{
    surface = IMG_Load(GET_TEXTURE_PATH("items/" + itemname));
    if(!surface) printf("[ERROR] Error loading item texture %s\n", itemname);
    std::string n = lang->translate(std::string("item.") + itemname + ".name");
    localizedName = (char*) malloc((int) n.size() + 1);
    memcpy(localizedName, n.c_str(), (int) n.size());
    localizedName[(int) n.size()] = 0;
    printf("Item %s with localized name %s\n", itemname, localizedName);
}

void Item::updateTexture()
{
    if(surface) texture = getTexture(surface);
}
