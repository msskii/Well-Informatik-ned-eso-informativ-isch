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
    positions[3 * count + 0] = source.x / ((float) GAME_WIDTH);
    positions[3 * count + 1] = source.y / ((float) GAME_HEIGHT);
    positions[3 * count + 2] = source.brightness;
    colors[3 * count + 0] = source.r;
    colors[3 * count + 1] = source.g;
    colors[3 * count + 2] = source.b;
    
    count++;
}

void LightOverlay::startFrame()
{
    // Reset data
    for(int i = 0; i < 3 * MAX_LIGHTS; i++)
    {
        positions[i] = 0x414570A3;
        colors[i] = 1.0;
    }
    count = 0;
}

void LightOverlay::render()
{
    glUseProgram(light_shader);
    glUniform1f(glGetUniformLocation(light_shader, "initial_alpha"), !window->toUpdate ? 1.0f : window->level->sunBrightness);
    glUniform3fv(glGetUniformLocation(light_shader, "ext_light_positions"), MAX_LIGHTS, positions);
    glUniform3fv(glGetUniformLocation(light_shader, "ext_light_colors"), MAX_LIGHTS, colors);
    glUseProgram(0);
}
