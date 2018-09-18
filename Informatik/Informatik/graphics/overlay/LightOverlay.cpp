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

    glUniform1f(glGetUniformLocation(shader_id, "initial_alpha"), !window->toUpdate ? 1.0 : 0.0);
    
    for(int i = 0; i < 2 * MAX_LIGHTS; i++) positions[i] = -100;
    int count = 0; // max 10
    for(int i = 0; i < (int) window->level->entities.size(); i++)
    {
        Explosion *projectile = dynamic_cast<Explosion*>(window->level->entities[i]);
        if(projectile != nullptr)
        {
            positions[2 * count + 0] = (projectile->data.x_pos + PLAYER_OFFSET_X + window->level->player->getOffsetX()) / (float) GAME_WIDTH;
            positions[2 * count + 1] = (projectile->data.y_pos + PLAYER_OFFSET_Y + window->level->player->getOffsetY()) / (float) GAME_HEIGHT;
            if(++count == MAX_LIGHTS) break;
        }
    }
    glUniform2fv(glGetUniformLocation(shader_id, "ext_lights"), MAX_LIGHTS, positions);
    
    glUseProgram(0);
}

void LightOverlay::drawOverlay(SDL_Renderer *renderer) {}

void LightOverlay::updateMenu(const uint8_t *keys)
{
    
}

void LightOverlay::onOpen() {}
void LightOverlay::onClose() {}
