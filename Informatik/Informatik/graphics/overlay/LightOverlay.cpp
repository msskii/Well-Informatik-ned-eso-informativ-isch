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
    
    glUseProgram(light_shader);
    
    // Copy data
    /**
    positions[4 * count + 0] = source.x / ((float) GAME_WIDTH);
    positions[4 * count + 1] = source.y / ((float) GAME_HEIGHT);
    positions[4 * count + 2] = source.brightness;
    positions[4 * count + 3] = source.radius;
    glowRatio = source.glowRatio;
    colors[4 * count + 0] = source.r;
    colors[4 * count + 1] = source.g;
    colors[4 * count + 2] = source.b;
    colors[4 * count + 3] = source.a;*/
    
    sources[count] = source;

    count++;
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
    for(int i = 0; i < 4 * MAX_LIGHTS; i++)
    {
        positions[i] = 0x414570A3; // NaN?
        colors[i] = 1.0;
    }
    count = 0;
}

void LightOverlay::render()
{
    glUseProgram(light_shader);
    
    glBindBuffer(GL_UNIFORM_BUFFER, lightBuffer);
    glBufferData(GL_UNIFORM_BUFFER, MAX_LIGHTS * sizeof(lightSource), sources, GL_DYNAMIC_DRAW);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, lightBuffer, 0, MAX_LIGHTS * sizeof(lightSource));
    glUniformBlockBinding(light_shader, glGetUniformBlockIndex(light_shader, "lightSources"), 0); // Send buffer?
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    
    /**
    glUniform1f(glGetUniformLocation(light_shader, "initial_alpha"), !window->toUpdate ? 1.0f : window->level->sunBrightness);
    glUniform4fv(glGetUniformLocation(light_shader, "ext_light_positions"), MAX_LIGHTS, positions);
    glUniform4fv(glGetUniformLocation(light_shader, "ext_light_colors"), MAX_LIGHTS, colors);
    glUniform1f(glGetUniformLocation(light_shader, "light_emit_to_reflect_ratio"), glowRatio);
    glUseProgram(light_shader_rotation);
    glUniform1f(glGetUniformLocation(light_shader_rotation, "initial_alpha"), !window->toUpdate ? 1.0f : window->level->sunBrightness);
    glUniform4fv(glGetUniformLocation(light_shader_rotation, "ext_light_positions"), MAX_LIGHTS, positions);
    glUniform4fv(glGetUniformLocation(light_shader_rotation, "ext_light_colors"), MAX_LIGHTS, colors);
    */
    
    glUseProgram(0);
}
