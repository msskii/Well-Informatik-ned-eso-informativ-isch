//
//  LightOverlay.cpp
//  Informatik
//
//  Created by Aaron Hodel on 17.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "LightOverlay.hpp"

GLuint LightOverlay::compileShader(const char *path, GLenum shaderType)
{
    GLuint id = glCreateShader(shaderType);
    filedata d = readFile(path);
    GLchar *f = (GLchar*) d.data;
    GLint l = (GLint) d.filesize;
    
    glShaderSource(id, 1, &f, &l);
    
    return id;
}

LightOverlay::LightOverlay(SDL_Renderer *renderer)
{    
    shouldLevelBeUpdated = true;
}

bool LightOverlay::shouldWindowClose() { return false; }

void LightOverlay::renderMenu(SDL_Renderer *renderer)
{
    
}

void LightOverlay::drawOverlay(SDL_Renderer *renderer) {}

void LightOverlay::updateMenu(const uint8_t *keys)
{
    
}

void LightOverlay::onOpen() {}
void LightOverlay::onClose() {}
