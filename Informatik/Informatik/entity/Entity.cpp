//
//  Entity.cpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Entity.hpp"

void Entity::addedToLevel(Level *l)
{
    level = l;
    onAddToLevel(l);
}
