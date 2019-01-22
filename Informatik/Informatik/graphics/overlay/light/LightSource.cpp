//
//  LightSource.cpp
//  Informatik
//
//  Created by Aaron Hodel on 21.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "LightSource.hpp"
#include "../../Window.hpp"

lightSource createLightSource(float x, float y, float brightness, float radius, uint32_t color, float glowRatio, float colorPart)
{
    lightSource src = {};
    src.x = x / ((float) GAME_WIDTH);
    src.y = y / ((float) GAME_HEIGHT);
    src.brightness = brightness;
    src.radius = radius;
    
    src.r = (float)((color >> 16) & 0xFF) / 255.0f;
    src.g = (float)((color >> 8) & 0xFF) / 255.0f;
    src.b = (float)((color >> 0) & 0xFF) / 255.0f;
    src.a = (float)((color >> 24) & 0xFF) / 255.0f;
    
    src.glowRatio = glowRatio;
    src.colorPart = colorPart;
    
    return src;
}

void moveLightSource(lightSource &src, float x, float y)
{
    src.x = x / ((float) GAME_WIDTH);
    src.y = y / ((float) GAME_HEIGHT);
}
