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
    float brightness = 1.0f;
    float r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f;
    float radius = 1.0f;
    float glowRatio = 1.0f;
}lightSource;

class Window;

class LightOverlay
{
private:
    GLfloat *positions = new float[4 * MAX_LIGHTS]; // x, y, brightness, radius
    GLfloat *colors = new float[4 * MAX_LIGHTS]; // r, g, b, a
    GLfloat glowRatio = 0.0f;
    Window *window;
    int count = 0;
    
public:
    LightOverlay();
    
    inline void open(Window *w) { window = w; }
    void startFrame();
    void addLight(lightSource ns);
    void addLight(float x, float y, float brightness, int color, float radius, float glowRatio);
    void render();
};

#endif /* LightOverlay_hpp */
