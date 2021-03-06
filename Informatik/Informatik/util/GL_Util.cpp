//
//  GL_Util.cpp
//  Informatik
//
//  Created by Aaron Hodel on 19.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "GL_Util.hpp"

// Two triangles form a quad
static const unsigned char *indicies = new unsigned char[6]
{
    0, 1, 2,
    0, 3, 2
};

// Indicies for the full image
static const float *uv_data = new float[8]
{
    0, 0,
    1, 0,
    1, 1,
    0, 1
};

float *texture_uvs = new float[8]; // Variable uv texture coords
float *verticies = new float[8]; // The verticies on the screen

GLuint uvBuffer = 0, uvBufferFull, vboID = 0, iboID = 0; // The different buffer objects
GLuint light_shader, const_shader, color_shader; // The shaders

GLuint compileShader(const char *path, GLenum shaderType)
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

GLuint createShader(const char* vertPath, const char* fragPath)
{
    GLuint vert = compileShader(GET_FILE_PATH(LEVEL_PATH, "shaders/" + vertPath), GL_VERTEX_SHADER);
    GLuint frag = compileShader(GET_FILE_PATH(LEVEL_PATH, "shaders/" + fragPath), GL_FRAGMENT_SHADER);
    GLuint shaderProgramID = glCreateProgram();
    
    glAttachShader(shaderProgramID, vert);
    glAttachShader(shaderProgramID, frag);
    glLinkProgram(shaderProgramID);
    
    GLint status;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &status);
    if(status != GL_TRUE)
    {
        printf("Couldn't link shader program...\n");
    }
    
    return shaderProgramID;
}

gl_texture getTexture(SDL_Surface *srfc)
{
	SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, srfc->w, srfc->h, 32, SDL_PIXELFORMAT_ARGB8888);
	SDL_BlitSurface(srfc, NULL, surface, NULL);

    gl_texture tex;
        
    glGenTextures(1, &tex.id);
    glBindTexture(GL_TEXTURE_2D, tex.id);
    tex.width = surface->w;
    tex.height = surface->h;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    SDL_FreeSurface(surface);

    return tex;
}

void deleteTexture(gl_texture texture)
{
    if(texture.id == 0) return; // No texture
    glDeleteTextures(1, &texture.id);
}

void setScreenSize(int w, int h)
{
    glViewport(0, 0, w, h);
    //glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glUseProgram(const_shader);
    glUniform2f(glGetUniformLocation(const_shader, "screenSize"), (float) w, (float) h);
    glUniform4f(glGetUniformLocation(const_shader, "col_mod"), 1, 1, 1, 1);
    glUseProgram(light_shader);
    glUniform2f(glGetUniformLocation(light_shader, "screenSize"), (float) w, (float) h);
}

void render(gl_texture texture, SDL_Rect src, SDL_Rect dst, GLuint shader)
{
    verticies[0]  = (float)((dst.x) / (GAME_WIDTH / 2.0f) - 1.0f); // upper left x transformed to -1 to 1
    verticies[1]  = -(float)((dst.y) / (GAME_HEIGHT / 2.0f) - 1.0f); // upper left x transformed to -1 to 1
    verticies[2]  = (float)((dst.x + dst.w) / (GAME_WIDTH / 2.0f) - 1.0f);
    verticies[3]  = verticies[1];
    verticies[4]  = verticies[2];
    verticies[5]  = -(float)((dst.y + dst.h) / (GAME_HEIGHT / 2.0f) - 1.0f);
    verticies[6]  = verticies[0];
    verticies[7]  = verticies[5];
    
    glUseProgram(shader);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    if(src.w != 0 && src.h != 0)
    {
        texture_uvs[0] = ((float) src.x) / ((float) texture.width); // top left
        texture_uvs[1] = ((float) (src.y)) / ((float) texture.height);
        texture_uvs[2] = ((float) (src.x + src.w)) / ((float) texture.width);
        texture_uvs[3] = texture_uvs[1];
        texture_uvs[4] = texture_uvs[2];
        texture_uvs[5] = ((float) (src.y + src.h)) / ((float) texture.height);
        texture_uvs[6] = texture_uvs[0];
        texture_uvs[7] = texture_uvs[5];
        
        glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
        glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), texture_uvs, GL_STREAM_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, uvBufferFull);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), verticies, GL_STREAM_DRAW);
    
    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glUniform1i(glGetUniformLocation(shader, "texture_sampler"), 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glUseProgram(0);
}

void renderWithRotation(gl_texture texture, SDL_Rect src, SDL_Rect dst, float rotationAngle, bool enabledShading)
{
    GLuint shader = enabledShading ? light_shader : const_shader;
    glUseProgram(shader);
    glUniform3f(glGetUniformLocation(shader, "rotation"), (float)((dst.x + dst.w / 2.0f) / (GAME_WIDTH / 2.0f) - 1.0f), -(float)((dst.y + dst.h / 2.0f) / (GAME_HEIGHT / 2.0f) - 1.0f), rotationAngle);
    render(texture, src, dst, shader);
}

void renderWithShading(gl_texture texture, SDL_Rect src, SDL_Rect dst)
{
    glUseProgram(light_shader);
    glUniform3f(glGetUniformLocation(light_shader, "rotation"), 0, 0, 0);
    render(texture, src, dst, light_shader);
}

void renderWithoutShading(gl_texture texture, SDL_Rect src, SDL_Rect dst, float alphamod)
{
    glUseProgram(const_shader);
    glUniform3f(glGetUniformLocation(const_shader, "rotation"), 0, 0, 0);
    glUniform4f(glGetUniformLocation(const_shader, "col_mod"), alphamod, 1, 1, 1);
    render(texture, src, dst, const_shader);
}

void setupGL()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    light_shader = createShader("shader_light.vert", "shader_light.frag");
    const_shader = createShader("shader_const.vert", "shader_const.frag");
    color_shader = createShader("shader_color.vert", "shader_color.frag");
    
    glGenBuffers(1, &uvBuffer);
    glGenBuffers(1, &vboID);
    
    glGenBuffers(1, &iboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned char), indicies, GL_STATIC_DRAW);
    
    glGenBuffers(1, &uvBufferFull);
    glBindBuffer(GL_ARRAY_BUFFER, uvBufferFull);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), uv_data, GL_STATIC_DRAW);
}

void fillRect(uint32_t col, SDL_Rect dst)
{
    verticies[0]  = (float)((dst.x) / (GAME_WIDTH / 2.0f) - 1.0f); // upper left x transformed to -1 to 1
    verticies[1]  = -(float)((dst.y) / (GAME_HEIGHT / 2.0f) - 1.0f); // upper left x transformed to -1 to 1
    verticies[2]  = (float)((dst.x + dst.w) / (GAME_WIDTH / 2.0f) - 1.0f);
    verticies[3]  = verticies[1];
    verticies[4]  = verticies[2];
    verticies[5]  = -(float)((dst.y + dst.h) / (GAME_HEIGHT / 2.0f) - 1.0f);
    verticies[6]  = verticies[0];
    verticies[7]  = verticies[5];
    
    glUseProgram(color_shader);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), verticies, GL_STREAM_DRAW);
    glUniform4f(glGetUniformLocation(color_shader, "color"), (float) ((col >> 24) & 0xFF), (float) ((col >> 0) & 0xFF), (float) ((col >> 8) & 0xFF), (float) ((col >> 16) & 0xFF));
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
    glUseProgram(0);
    
    glDisableVertexAttribArray(0);
}

void drawRect(uint32_t col, SDL_Rect src)
{
    
}

