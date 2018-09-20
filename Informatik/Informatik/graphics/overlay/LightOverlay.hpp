//
//  LightOverlay.hpp
//  Informatik
//
//  Created by Aaron Hodel on 17.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef LightOverlay_hpp
#define LightOverlay_hpp

#include "../../util/GL_Util.hpp"

#define MAX_LIGHTS 40
typedef struct lightSource
{
    float x = 0.0, y = 0.0;
    float brightness = 1.0;
    float r = 1.0, g = 1.0, b = 1.0;
} lightSource;

class Window;

class LightOverlay
{
private:
    GLfloat *positions = new float[3 * MAX_LIGHTS]; // x, y, brightness
    GLfloat *colors = new float[3 * MAX_LIGHTS]; // r, g, b
    Window *window;
    int count = 0;
    
public:
    LightOverlay();
    
    inline void open(Window *w) { window = w; }
    void startFrame();
    void addLight(lightSource ns);
    void render();
};

#endif /* LightOverlay_hpp */
