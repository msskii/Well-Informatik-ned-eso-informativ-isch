//
//  Fireflies.hpp
//  Informatik
//
//  Created by Keanu Gleixner on 24.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Fireflies_hpp
#define Fireflies_hpp

#include "../Entity.hpp"

#include <stdio.h>

class Fireflies : public Entity
{
protected:
    
public:
    int Flycount = 2;
    float flypos[8];
   
    Fireflies(float x, float y);
    
    void onAddToLevel(Level *level) override;
    void render(int xoff, int yoff) override;
    void update(const uint8_t *keys) override;
};

#endif /* Fireflies_hpp */
