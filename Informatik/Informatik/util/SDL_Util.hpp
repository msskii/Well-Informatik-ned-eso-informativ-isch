//
//  SDL_Util.hpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef SDL_Util_h
#define SDL_Util_h

#include "Math_Util.hpp"

#ifdef __APPLE__
#  include <SDL2/SDL.h> // Other path than on windows
#  include <SDL2_ttf/SDL_ttf.h>
#  include <SDL2_net/SDL_net.h>
#  include <SDL2_mixer/SDL_mixer.h>
#  include <SDL2_image/SDL_image.h>
#else
#  include <SDL.h>
#  include <SDL_ttf.h>
#  include <SDL_net.h>
#  include <SDL_mixer.h>
#  include <SDL_image.h>
#endif

#include <string>
#include "Logger.hpp"

#define COLOR(r, col) SDL_SetRenderDrawColor(r, ((col) >> 16) & 0xFF, ((col) >> 8) & 0xFF, (col) & 0xFF, ((col) >> 24) & 0xFF)
#define TO_COLOR(col) SDL_Color({ (uint8_t) ((col) >> 16), (uint8_t) ((col) >> 8), (uint8_t) (col), (uint8_t) ((col) >> 24) })

#define TRANSFORM_LEVEL_POS(rect, xoff, yoff) {rect.x += (int) xoff + PLAYER_OFFSET_X; rect.y += (int) yoff + PLAYER_OFFSET_Y;}

extern TTF_Font *font;
extern float SCALE_X, SCALE_Y;

/**
typedef struct cachedTexture
{
    SDL_Texture *texture = nullptr;
    int textwidth, textheight;
} cachedTexture;*/

#include "GL_Util.hpp"

typedef struct cachedTexture
{
    GLuint id = 0;
    int width = 0, height = 0;
    float scale = 0.0f;
    
    inline gl_texture getGL() { return gl_texture({width, height, id}); }
} cachedTexture;

extern void deleteTexture(cachedTexture &texture);

extern float drawTextAspect(const char *text, uint32_t color, SDL_Rect dst, cachedTexture &texture, bool forceUpdate); // Keep aspect ratio
extern float drawTextCentered(const char *text, uint32_t color, SDL_Rect dst, cachedTexture &texture, bool forceUpdate); // Keep aspect ratio & center to the width
extern char scancodeToChar(SDL_Scancode code, SDL_Keymod mods);


#endif /* SDL_Util_h */
