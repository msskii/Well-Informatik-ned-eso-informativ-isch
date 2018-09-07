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
    SDL_Surface *surface = nullptr;
    SDL_Texture *texture = nullptr;
    
    Item(const char* itemname, SDL_Renderer *renderer);
};

#endif /* Item_hpp */
