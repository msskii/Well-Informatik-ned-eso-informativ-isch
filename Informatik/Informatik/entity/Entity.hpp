//
//  Entity.hpp
//  Informatik
//
//  Created by Aaron Hodel on 21.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp


enum DIRECTION
{
    DOWN = 0,
    UP,
    LEFT,
    RIGHT
};

typedef struct SerializedEntity
{
    int x_pos = 0;
    int y_pos = 0;
    int maxhealth = 0;
} SerializedEntity;

class Entity
{
protected:
    
public:
    float health;
    SerializedEntity data;
};

#endif /* Entity_hpp */
