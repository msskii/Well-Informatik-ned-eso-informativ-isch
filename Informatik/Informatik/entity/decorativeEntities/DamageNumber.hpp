//
//  DamageNumber.hpp
//  Informatik
//
//  Created by Keanu Gleixner on 26.02.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef DamageNumber_hpp
#define DamageNumber_hpp

#include <stdio.h>
#include "../Entity.hpp"
#include "../../util/TextRenderer.hpp"

class DamageNumber : public Entity {
private:
    std::string damageText;
    int ticks = 0;
    int ticksAlive = 60;
    float vx,vy;
    uint32_t color = 0xFFFFFFFF;
    
public:
    
    DamageNumber(float x, float y, int amount);
    
    void render(int xoff, int yoff) override;
    void update(const uint8_t *keys) override;
    void onAddToLevel(Level *level) override;
};


#endif /* DamageNumber_hpp */
