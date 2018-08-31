//
//  SDL_Util.hpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef SDL_Util_h
#define SDL_Util_h

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


#define TEXTURE_PATH std::string("assets/textures/")
#define FONT_PATH std::string("assets/fonts/")
#define LEVEL_PATH std::string("assets/data/")
#define AUDIO_PATH std::string("assets/audio/")

#define GET_VARIANT_PATH(texture_name, variant_num) (TEXTURE_PATH + texture_name + std::to_string(variant_num) + ".png").c_str()
#define GET_FILE_PATH(initpath, filename) (initpath + filename).c_str()

#define COLOR(r, col) SDL_SetRenderDrawColor(r, ((col) >> 16) & 0xFF, ((col) >> 8) & 0xFF, (col) & 0xFF, ((col) >> 24) & 0xFF)
#define TO_COLOR(col) SDL_Color({ (uint8_t) ((col) >> 16), (uint8_t) ((col) >> 8), (uint8_t) (col), (uint8_t) ((col) >> 24) })

extern TTF_Font *font;
extern float SCALE_X, SCALE_Y;

extern void drawText(SDL_Renderer *renderer, const char *text, int color, int x, int y);
extern void drawTextAspect(SDL_Renderer *renderer, const char *text, int color, int x, int y, int w, int h); // Keep aspect ratio
extern void drawTextCentered(SDL_Renderer *renderer, const char *text, int color, int x, int y, int w, int h); // Keep aspect ratio & center to the width
extern char scancodeToChar(SDL_Scancode code, SDL_Keymod mods);

#endif /* SDL_Util_h */
