//
//  Enemy.hpp
//  Informatik
//
//  Created by Aaron Hodel on 04.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "../entity/Entity.hpp"
#include <vector>

enum ATTACK_STATE
{
    READY_TO_ATTACK,
    ATTACKING,
    ATTACK_DONE,
    RECHARGING
};

class Enemy;
typedef void (*attackFunction)(Enemy *e, Level *level);

class Enemy : public Entity
{
private:
    std::vector<attackFunction> attacks;
    ATTACK_STATE attackState = READY_TO_ATTACK;
    
public:
    virtual bool isInside(float x, float y) = 0;
};

#endif /* Enemy_hpp */
