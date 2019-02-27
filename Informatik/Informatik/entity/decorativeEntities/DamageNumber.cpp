//
//  DamageNumber.cpp
//  Informatik
//
//  Created by Keanu Gleixner on 26.02.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "DamageNumber.hpp"
#include "../level/Level.hpp"

#define GRAVITY 0.4f

DamageNumber::DamageNumber(float x, float y, int damage){
    data.width = GAME_WIDTH / 30 + damage * GAME_WIDTH / 1000;
    data.height = GAME_HEIGHT / 30 + damage * GAME_WIDTH / 1000;
    data.x_pos = x - (data.width / 2);
    data.y_pos = y - (data.height / 2);
    damageText = std::to_string(damage);
    vx = 3.0;
    vy = 10.0;

}

void DamageNumber::update(const uint8_t *keys){
    ticks++;
    if (ticksAlive <= ticks) {
        level->removeEntity(this);
    }
    vy -= GRAVITY;
    data.x_pos += vx;
    data.y_pos -= vy;
    if(ticks > ticksAlive / 2)color = uint32_t(0x00FFFFFF) + (uint32_t((1.0 - (float(ticks - (ticksAlive / 2)) / float(ticksAlive / 2))) * 0xFF000000) & 0xFF000000);
}

void DamageNumber::render(int xoff, int yoff){
    SDL_Rect r = getBoundingBox();
    TRANSFORM_LEVEL_POS(r, xoff, yoff);
    drawTextAspect(damageText.c_str(), color, r);
}

void DamageNumber::onAddToLevel(Level *l){
}
