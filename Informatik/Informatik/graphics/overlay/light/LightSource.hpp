//
//  LightSource.hpp
//  Informatik
//
//  Created by Aaron Hodel on 21.01.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef LightSource_hpp
#define LightSource_hpp

#include <stdint.h>

typedef struct lightSource
{
    // first vec4
    float x = 0.0, y = 0.0; // Position
    float brightness = 1.0f; // The brightness of this light
    float radius = 1.0f; // The radius this light may have
    
    // Second vec4
    float r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f; // The color modifier (Black for no change)
    
    // Third vec4
    float glowRatio = 1.0f; // Sunlight reflection
    float colorPart = 0.0f; // How much color will be mixed in
    float _a, _b; // To fill stuff up (16 bytes aligned)
} lightSource;

lightSource createLightSource(float x, float y, float brightness, float radius, uint32_t color, float glowRatio, float colorPart);
void moveLightSource(lightSource &src, float x, float y);

#endif /* LightSource_hpp */
