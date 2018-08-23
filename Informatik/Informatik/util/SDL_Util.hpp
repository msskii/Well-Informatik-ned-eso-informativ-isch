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
#  include <SDL2_ttf/SDL_ttf.h> // Don't know this one on windows...
#else
#  include <SDL2.h>
#  include <SDL_ttf.h>
#endif

#include "Logger.hpp"

#define COLOR(r, col) SDL_SetRenderDrawColor(r, ((col) >> 16) & 0xFF, ((col) >> 8) & 0xFF, (col) & 0xFF, ((col) >> 24) & 0xFF)

extern TTF_Font *font;

extern void drawText(SDL_Renderer *renderer, const char *text, SDL_Color color, int x, int y);
extern void drawText(SDL_Renderer *renderer, const char *text, SDL_Color color, int x, int y, int w, int h);



#endif /* SDL_Util_h */
