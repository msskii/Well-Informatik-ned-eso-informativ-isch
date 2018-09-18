//
//  LightOverlay.cpp
//  Informatik
//
//  Created by Aaron Hodel on 17.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "LightOverlay.hpp"

LightOverlay::LightOverlay(GLuint shader)
{
    printf("[INFO] Initialized GLEW: \n\tGL   Version: %s\n\tGLSL Version: %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
    
    shader_id = shader;
    shouldLevelBeUpdated = true;
}

bool LightOverlay::shouldWindowClose() { return false; }

void LightOverlay::renderMenu(SDL_Renderer *renderer)
{    
    int x, y;
    SDL_GetMouseState(&x, &y);
    float x_pos_rel = (float) x / (float) GAME_WIDTH;
    float y_pos_rel = (float) y / (float) GAME_HEIGHT;

    glUseProgram(shader_id);
    glUniform2f(glGetUniformLocation(shader_id, "mousepos"), x_pos_rel, y_pos_rel);
    glUseProgram(0);
}

void LightOverlay::drawOverlay(SDL_Renderer *renderer) {}

void LightOverlay::updateMenu(const uint8_t *keys)
{
    
}

void LightOverlay::onOpen() {}
void LightOverlay::onClose() {}
