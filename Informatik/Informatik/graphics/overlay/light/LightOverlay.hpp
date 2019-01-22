//
//  LightOverlay.hpp
//  Informatik
//
//  Created by Aaron Hodel on 17.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef LightOverlay_hpp
#define LightOverlay_hpp

#include "LightSource.hpp"
#include "../../../util/GL_Util.hpp"

#define MAX_LIGHTS 40

class Window;

class LightOverlay
{
private:
    GLfloat glowRatio = 0.0f;
    
    GLuint lightBuffer;
    lightSource *sources = new lightSource[MAX_LIGHTS]; // Testing to pass a whole array with all information to the shader for easy modification
    
    Window *window;
    int count = 0;
    
public:
    LightOverlay();
    
    void sendStuff(GLuint shader);
    inline void open(Window *w) { window = w; glGenBuffers(1, &lightBuffer); }
    void startFrame();
    
    void injectLight(lightSource source);
    //void addLight(lightSource ns);
    void addLight(float x, float y, float brightness, int color, float radius, float glowRatio);
    //void addLight(float x, float y, float brightness, int r, int g, int b, int a, float radius, float glowRatio);
    void render();
};

#endif /* LightOverlay_hpp */
