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
    
    glCompileShader(id);
    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE)
    {
        printf("[ERROR] Couldn't compile Shader: \n");
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &status);
        char *msg = (char*) malloc(status + 1);
        int len;
        glGetShaderInfoLog(id, status, &len, msg);
        msg[status] = 0;
        printf("%s\n", msg);
        free(msg);
    }
    
    return id;
}

LightOverlay::LightOverlay(SDL_Renderer *renderer)
{
    printf("[INFO] Initialized GLEW: \n\tGL   Version: %s\n\tGLSL Version: %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

    compileShader(GET_FILE_PATH(LEVEL_PATH, "shader.vert"), GL_VERTEX_SHADER);
    shouldLevelBeUpdated = true;
}

bool LightOverlay::shouldWindowClose() { return false; }

void LightOverlay::renderMenu(SDL_Renderer *renderer)
{    
    glColor4f(1, 0, 1, 1);
    glBegin(GL_TRIANGLES);
    
    glVertex2d(0, 0);
    glVertex2d(0, 1);
    glVertex2d(1, 1);

    glEnd();
}

void LightOverlay::drawOverlay(SDL_Renderer *renderer) {}

void LightOverlay::updateMenu(const uint8_t *keys)
{
    
}

void LightOverlay::onOpen() {}
void LightOverlay::onClose() {}
