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
    
    texture_width = surface->w;
    texture_height = surface->h;
    
    if(!strcmp(itemname, "coin"))
    {
        texture_width = 32;
        texture_height = 32;
        animationSpeed = 5;
        animationFrames = 12;
    }
    if(!strcmp(itemname, "glob_of_slime"))
    {
        texture_width = 32;
        texture_height = 32;
        animationSpeed = 0;
        animationFrames = 1;
    }
}

void Item::updateTexture()
{
    if(surface != NULL) texture = getTexture(surface);
}
