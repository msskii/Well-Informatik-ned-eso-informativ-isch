//
//  Slime.hpp
//  Informatik
//
//  Created by Aaron Hodel on 04.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Slime_hpp
#define Slime_hpp

#include "Enemy.hpp"

class Slime : public Enemy
{
private:
    
public:
    Slime(float x, float y);
    
    bool isInside(float x, float y);
    void onAddToLevel(Level *level);
    void render(SDL_Renderer *renderer, int xoff, int yoff);
    void update(const uint8_t *keys);
};

#endif /* Slime_hpp */
