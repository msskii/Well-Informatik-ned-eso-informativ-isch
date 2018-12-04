 //
//  SDL_Util.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "SDL_Util.hpp"
#include "FileReader.hpp"
#include "../config.h"

TTF_Font *font = nullptr;
float SCALE_X = 0, SCALE_Y = 0;

void deleteTexture(cachedTexture &texture)
{
    if(texture.id) glDeleteTextures(1, &texture.id);
    texture.id = 0; // Set reference's id to zero
}

float drawTextAspect(const char *text, uint32_t color, SDL_Rect dst, cachedTexture &texture_cache, bool forceUpdate)
{
    if(font == nullptr)
    {
        INFO("Font not yet initialized");
        return 0;
    }
    
    if(texture_cache.id == 0 || forceUpdate)
    {
        if(forceUpdate) deleteTexture(texture_cache);
        
        SDL_Surface *text_surface = TTF_RenderText_Solid(font, text, TO_COLOR(color));
        if(text_surface == nullptr)
        {
            return 0;
        }

        SDL_Surface *srfc = SDL_CreateRGBSurfaceWithFormat(0, text_surface->w, text_surface->h, 32, SDL_PIXELFORMAT_ARGB8888);
        SDL_SetSurfaceBlendMode(srfc, SDL_BLENDMODE_BLEND);
        SDL_SetSurfaceAlphaMod(srfc, color >> 24);
        SDL_BlitSurface(text_surface, NULL, srfc, NULL);
        
        if(srfc == nullptr) return 0;
        gl_texture tmp = getTexture(srfc); // Copy only id since width & height are different...
        texture_cache.id = tmp.id;
        texture_cache.width = tmp.width;
        texture_cache.height = tmp.height;
        
        float scaleX = (float) dst.w / (float) srfc->w;
        float scaleY = (float) dst.h / (float) srfc->h;
        texture_cache.scale = (float) fmin(scaleX, scaleY); // Smaller scale value
        
        // Clean up
        SDL_FreeSurface(srfc);

        if(texture_cache.id == 0) return texture_cache.scale; // texture creation failed...
    }
    
    // We have a texture, just render that...
    dst.w = (int) ((float) texture_cache.width * texture_cache.scale);
    dst.h = (int) ((float) texture_cache.height * texture_cache.scale);
    renderWithoutShading(texture_cache.getGL(), {0, 0, 0, 0}, dst);
    
    return texture_cache.scale;
}

float drawTextCentered(const char *text, uint32_t color, SDL_Rect dst, cachedTexture &texture_cache, bool forceUpdate)
{
    if(font == nullptr)
    {
        INFO("Font not yet initialized");
        return 0;
    }
    
    if(texture_cache.id == 0 || forceUpdate)
    {
        if(forceUpdate) deleteTexture(texture_cache);
        
        SDL_Surface *text_surface = TTF_RenderText_Solid(font, text, TO_COLOR(color));
        if(text_surface == nullptr)
        {
            return 0;
        }
        
        SDL_Surface *srfc = SDL_CreateRGBSurfaceWithFormat(0, text_surface->w, text_surface->h, 32, SDL_PIXELFORMAT_ARGB8888);
        SDL_SetSurfaceBlendMode(srfc, SDL_BLENDMODE_BLEND);
        SDL_SetSurfaceAlphaMod(srfc, color >> 24);
        SDL_BlitSurface(text_surface, NULL, srfc, NULL);
        
        if(srfc == nullptr) return 0;
        gl_texture tmp = getTexture(srfc); // Copy only id since width & height are different...
        texture_cache.id = tmp.id;
        texture_cache.width = tmp.width;
        texture_cache.height = tmp.height;
        
        float scaleX = (float) dst.w / (float) srfc->w;
        float scaleY = (float) dst.h / (float) srfc->h;
        texture_cache.scale = (float) fmin(scaleX, scaleY); // Smaller scale value
        
        // Clean up
        SDL_FreeSurface(srfc);
        
        if(texture_cache.id == 0) return texture_cache.scale; // texture creation failed...
    }
    
    // We have a texture, just render that...
    int neww = (int) ((float) texture_cache.width * texture_cache.scale);
    int newh = (int) ((float) texture_cache.height * texture_cache.scale);
    dst.x += (dst.w - neww) / 2.0f;
    dst.y += (dst.h - newh) / 2.0f;
    dst.w = neww;
    dst.h = newh;
    renderWithoutShading(texture_cache.getGL(), {0, 0, 0, 0}, dst);
    
    return texture_cache.scale;
}

char scancodeToChar(SDL_Scancode code, SDL_Keymod mod)
{
    bool shift = mod & KMOD_SHIFT;
    switch(code)
    {
        case SDL_SCANCODE_A:
            return shift ? 'A' : 'a';
        case SDL_SCANCODE_B:
            return shift ? 'B' : 'b';
        case SDL_SCANCODE_C:
            return shift ? 'C' : 'c';
        case SDL_SCANCODE_D:
            return shift ? 'D' : 'd';
        case SDL_SCANCODE_E:
            return shift ? 'E' : 'e';
        case SDL_SCANCODE_F:
            return shift ? 'F' : 'f';
        case SDL_SCANCODE_G:
            return shift ? 'G' : 'g';
        case SDL_SCANCODE_H:
            return shift ? 'H' : 'h';
        case SDL_SCANCODE_I:
            return shift ? 'I' : 'i';
        case SDL_SCANCODE_J:
            return shift ? 'J' : 'j';
        case SDL_SCANCODE_K:
            return shift ? 'K' : 'k';
        case SDL_SCANCODE_L:
            return shift ? 'L' : 'l';
        case SDL_SCANCODE_M:
            return shift ? 'M' : 'm';
        case SDL_SCANCODE_N:
            return shift ? 'N' : 'n';
        case SDL_SCANCODE_O:
            return shift ? 'O' : 'o';
        case SDL_SCANCODE_P:
            return shift ? 'P' : 'p';
        case SDL_SCANCODE_Q:
            return shift ? 'Q' : 'q';
        case SDL_SCANCODE_R:
            return shift ? 'R' : 'r';
        case SDL_SCANCODE_S:
            return shift ? 'S' : 's';
        case SDL_SCANCODE_T:
            return shift ? 'T' : 't';
        case SDL_SCANCODE_U:
            return shift ? 'U' : 'u';
        case SDL_SCANCODE_V:
            return shift ? 'V' : 'v';
        case SDL_SCANCODE_W:
            return shift ? 'W' : 'w';
        case SDL_SCANCODE_X:
            return shift ? 'X' : 'x';
        case SDL_SCANCODE_Y:
            return shift ? 'Y' : 'y';
        case SDL_SCANCODE_Z:
            return shift ? 'Z' : 'z';
        case SDL_SCANCODE_0:
            return shift ? '=' : '0';
        case SDL_SCANCODE_1:
            return shift ? '+' : '1';
        case SDL_SCANCODE_2:
            return shift ? '\"' : '2';
        case SDL_SCANCODE_3:
            return shift ? '*' : '3';
        case SDL_SCANCODE_4:
            return shift ? '#' : '4';
        case SDL_SCANCODE_5:
            return shift ? '%' : '5';
        case SDL_SCANCODE_6:
            return shift ? '&' : '6';
        case SDL_SCANCODE_7:
            return shift ? '/' : '7';
        case SDL_SCANCODE_8:
            return shift ? '(' : '8';
        case SDL_SCANCODE_9:
            return shift ? ')' : '9';
		case SDL_SCANCODE_KP_0:
			return shift ? '\0' : '0';
		case SDL_SCANCODE_KP_1:
			return shift ? '\0' : '1';
		case SDL_SCANCODE_KP_2:
			return shift ? '\0' : '2';
		case SDL_SCANCODE_KP_3:
			return shift ? '\0' : '3';
		case SDL_SCANCODE_KP_4:
			return shift ? '\0' : '4';
		case SDL_SCANCODE_KP_5:
			return shift ? '\0' : '5';
		case SDL_SCANCODE_KP_6:
			return shift ? '\0' : '6';
		case SDL_SCANCODE_KP_7:
			return shift ? '\0' : '7';
		case SDL_SCANCODE_KP_8:
			return shift ? '\0' : '8';
		case SDL_SCANCODE_KP_9:
			return shift ? '\0' : '9';
		case SDL_SCANCODE_PERIOD:
		case SDL_SCANCODE_KP_PERIOD:
			return shift ? ':' : '.';
        case SDL_SCANCODE_COMMA:
        case SDL_SCANCODE_KP_COMMA:
            return shift ? ';' : ',';
        case SDL_SCANCODE_NONUSBACKSLASH:
            return shift? '>' : '<';
        case SDL_SCANCODE_MINUS:
            return shift? '?' : '\'';
        case SDL_SCANCODE_EQUALS:
            return shift? '`' : '^';
        case SDL_SCANCODE_BACKSPACE:
            return '\x08';
        case SDL_SCANCODE_SPACE:
            return ' ';
        case SDL_SCANCODE_RIGHT:
        case SDL_SCANCODE_LEFT:
        case SDL_SCANCODE_UP:
        case SDL_SCANCODE_DOWN:
		case SDL_SCANCODE_RETURN:
        case SDL_SCANCODE_LSHIFT: // No characters for this key
        case SDL_SCANCODE_RSHIFT:
        case SDL_SCANCODE_CAPSLOCK:
        case SDL_SCANCODE_TAB:
        case SDL_SCANCODE_LALT:
        case SDL_SCANCODE_RALT:
            return '\0';
        default:
            printf("[INFO] Unknown scancode: %d\n", code);
            return '?'; // Unknown char
    }
}
