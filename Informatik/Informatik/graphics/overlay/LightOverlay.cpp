//
//  LightOverlay.cpp
//  Informatik
//
//  Created by Aaron Hodel on 17.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "LightOverlay.hpp"
#include "../Window.hpp"

LightOverlay::LightOverlay() {}

void LightOverlay::addLight(lightSource source)
{
    if(count >= MAX_LIGHTS) return; // No more lights!
    source.x /= ((float) GAME_WIDTH);
    source.y /= ((float) GAME_HEIGHT);
    sources[count++] = source;
}

void LightOverlay::addLight(float x, float y, float brightness, int color, float radius, float glowRatio)
{
    lightSource ls;
    
    ls.brightness = brightness;
    ls.x = x;
    ls.y = y;
    ls.radius = radius;
    ls.glowRatio = glowRatio;
    
    ls.r = (float)((color >> 16) & 0xFF) / 255.0f;
    ls.g = (float)((color >> 8) & 0xFF) / 255.0f;
    ls.b = (float)((color >> 0) & 0xFF) / 255.0f;
    ls.a = (float)((color >> 24) & 0xFF) / 255.0f;
    
    addLight(ls);
}

void LightOverlay::startFrame()
{
    // Reset data
    for(int i = 0; i < MAX_LIGHTS; i++)
    {
        sources[i].x = -100;
        sources[i].y = -100;
    }
    count = 0;
}

void sendStuff(GLuint shader, lightSource *sources, GLuint lightBuffer)
{
    glUseProgram(shader);
    glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer);
    glBufferData(GL_UNIFORM_BUFFER, MAX_LIGHTS * sizeof(lightSource), sources, GL_DYNAMIC_DRAW); // Store data
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, lightBuffer, 0, MAX_LIGHTS * sizeof(lightSource)); // Bind the whole range of it
    glUniformBlockBinding(shader, glGetUniformBlockIndex(shader, "lightSources"), 0); // Send buffer to shader
    glBindBuffer(GL_UNIFORM_BUFFER, 0); // Unbind buffer
    glUseProgram(0); // Unbind shader

}

void LightOverlay::render()
{
    sendStuff(light_shader, sources, lightBuffer);
    sendStuff(light_shader_rotation, sources, lightBuffer);
}
