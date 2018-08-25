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
#else
#  include <SDL.h>
#  include <SDL_ttf.h>
#  include <SDL_net.h>
#endif

#include "Logger.hpp"

#define COLOR(r, col) SDL_SetRenderDrawColor(r, ((col) >> 16) & 0xFF, ((col) >> 8) & 0xFF, (col) & 0xFF, ((col) >> 24) & 0xFF)

#define TO_COLOR(col) SDL_Color({ (uint8_t) ((col) >> 16), (uint8_t) ((col) >> 8), (uint8_t) (col), (uint8_t) ((col) >> 24) })

extern TTF_Font *font;
extern float SCALE_X, SCALE_Y;

extern void drawText(SDL_Renderer *renderer, const char *text, int color, int x, int y);
extern void drawTextFit(SDL_Renderer *renderer, const char *text, int color, int x, int y, int w, int h); // Scale to fit
extern void drawTextAspect(SDL_Renderer *renderer, const char *text, int color, int x, int y, int w, int h); // Keep aspect ratio
extern char scancodeToChar(SDL_Scancode code, SDL_Keymod mods);


#endif /* SDL_Util_h */
