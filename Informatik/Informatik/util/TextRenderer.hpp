//
//  TextRenderer.hpp
//  Informatik
//
//  Created by Aaron Hodel on 09.02.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#ifndef TextRenderer_hpp
#define TextRenderer_hpp

#include "GL_Util.hpp"
#include "SDL_Util.hpp"

#define FONT_RESOLUTION 64

extern gl_texture *char_textures;

extern void setupTextRenderer(const char *fontFile);
extern void drawText(const char *text, SDL_Rect dst);

#endif /* TextRenderer_hpp */
