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

SDL_Surface* drawText(const char *text, uint32_t color, SDL_Rect dst, cachedTexture &texture_cache, bool forceUpdate, bool centered)
{
    SDL_Surface *text_surface = nullptr;
    if(font == nullptr)
    {
        INFO("Font not yet initialized");
        return nullptr;
    }
    
    if(texture_cache.id == 0 || forceUpdate)
    {
        if(forceUpdate) deleteTexture(texture_cache);
        
        text_surface = TTF_RenderText_Solid(font, text, TO_COLOR(color));
        if(text_surface == nullptr)
        {
            return nullptr;
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
        
        if(texture_cache.id == 0) return nullptr; // texture creation failed...
    }
    
    // We have a texture, just render that...
    int neww = (int) ((float) texture_cache.width * texture_cache.scale);
    int newh = (int) ((float) texture_cache.height * texture_cache.scale);
    if(centered)
    {
        int neww = (int) ((float) texture_cache.width * texture_cache.scale);
        int newh = (int) ((float) texture_cache.height * texture_cache.scale);
        dst.x += (dst.w - neww) / 2;
        dst.y += (dst.h - newh) / 2;
    }
    dst.w = neww;
    dst.h = newh;
    renderWithoutShading(texture_cache.getGL(), {0, 0, 0, 0}, dst);
    
    return text_surface;
}

SDL_Surface* drawTextAspect(const char *text, uint32_t color, SDL_Rect dst, cachedTexture &texture_cache, bool forceUpdate)
{
    return drawText(text, color, dst, texture_cache, forceUpdate, false);
}

SDL_Surface* drawTextCentered(const char *text, uint32_t color, SDL_Rect dst, cachedTexture &texture_cache, bool forceUpdate)
{
    return drawText(text, color, dst, texture_cache, forceUpdate, true);
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
            return shift ? '>' : '<';
        case SDL_SCANCODE_MINUS:
            return shift ? '?' : '\'';
        case SDL_SCANCODE_EQUALS:
            return shift ? '`' : '^';
        case SDL_SCANCODE_SLASH:
            return shift ? '_' : '-';
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

void brighten(SDL_Surface *surface, float multiplier)
{
    uint32_t *pixels = (uint32_t*) surface->pixels;
    SDL_PixelFormat *fml = surface->format;
    for(int i = 0; i < surface->w * surface->h; i++)
    {
        uint32_t cp = ((uint32_t*) surface->pixels)[i];
        uint32_t r = (uint32_t) ((cp & fml->Rmask) * (multiplier + 1.0f));
        if (r > fml->Rmask) r = fml->Rmask;
        uint32_t g = (uint32_t) ((cp & fml->Gmask) * (multiplier + 1.0f));
        if (g > fml->Gmask) g = fml->Gmask;
        uint32_t b = (uint32_t) ((cp & fml->Bmask) * (multiplier + 1.0f));
        if (b > fml->Bmask) b = fml->Bmask;
        pixels[i] = (cp & fml->Amask) | r | g | b;
    }
}

//
void tint(SDL_Surface *surface, int16_t rAmount, int16_t gAmount, int16_t bAmount)
{
    uint32_t *pixels = (uint32_t*) surface->pixels;
    SDL_PixelFormat *fml = surface->format;
    for(int i = 0; i < surface->w * surface->h; i++)
    {
        uint32_t cp = ((uint32_t*) surface->pixels)[i];
        
        uint8_t r = ((cp & fml->Rmask) >> fml->Rshift) + rAmount;
        if(rAmount > 0 && r < ((cp & fml->Rmask) >> fml->Rshift)) r = 255;
        if(rAmount < 0 && r > ((cp & fml->Rmask) >> fml->Rshift)) r = 0;

        uint8_t g = ((cp & fml->Gmask) >> fml->Gshift) + gAmount;
        if(gAmount > 0 && g < ((cp & fml->Gmask) >> fml->Gshift)) g = 255;
        if(gAmount < 0 && g > ((cp & fml->Gmask) >> fml->Gshift)) g = 0;
        
        uint8_t b = ((cp & fml->Bmask) >> fml->Bshift) + bAmount;
        if(bAmount > 0 && b < ((cp & fml->Bmask) >> fml->Bshift)) b = 255;
        if(bAmount < 0 && b > ((cp & fml->Bmask) >> fml->Bshift)) b = 0;
        
        pixels[i] = (cp & fml->Amask) | r << fml->Rshift | g << fml->Gshift | b << fml->Bshift;
    }
}

void adjustAlpha(SDL_Surface *surface, int newAlpha){
    uint32_t *pixels = (uint32_t*) surface->pixels;
    SDL_PixelFormat *fml = surface->format;
    for(int i = 0; i < surface->w * surface->h; i++){
        uint32_t cp = ((uint32_t*) surface->pixels)[i];
        if (cp != 0) {
            pixels[i] =(newAlpha << fml->Ashift) | (cp & fml->Rmask) | (cp & fml->Gmask) | (cp & fml->Bmask);
        }
    }
}

bool hitboxOverlap(SDL_Rect a, SDL_Rect b){

    return oneDimensionalOverlap(a.x, a.x + a.w, b.x, b.x + b.w) && oneDimensionalOverlap(a.y, a.y + a.h, b.y, b.y + b.h);
}

bool oneDimensionalOverlap(int box1min ,int box1max, int box2min, int box2max){
    return !(box1min >= box2max || box2min >= box1max);
}
