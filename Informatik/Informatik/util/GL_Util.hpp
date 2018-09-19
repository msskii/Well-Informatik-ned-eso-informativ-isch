//
//  GL_Util.hpp
//  Informatik
//
//  Created by Aaron Hodel on 19.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef GL_Util_hpp
#define GL_Util_hpp

#include "SDL_Util.hpp"
#include "FileReader.hpp"
#include "../config.h"

typedef struct gl_texture
{
    int width, height;
    GLuint id = 0;
} gl_texture;

extern GLuint light_shader, const_shader, color_shader; // The shaders

extern GLuint compileShader(const char *path, GLenum shaderType);
extern GLuint createShader(const char *vert, const char *frag);

extern void setupGL();
extern gl_texture getTexture(SDL_Surface *surface);
extern void deleteTexture(gl_texture texture);
extern void renderWithShading(gl_texture texture, SDL_Rect src, SDL_Rect dst);
extern void renderWithoutShading(gl_texture texture, SDL_Rect src, SDL_Rect dst);
extern void fillRect(uint32_t col, SDL_Rect src);
extern void drawRect(uint32_t col, SDL_Rect src);

#endif /* GL_Util_hpp */
