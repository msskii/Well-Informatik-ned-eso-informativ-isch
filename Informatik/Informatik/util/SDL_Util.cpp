 //
//  SDL_Util.cpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "SDL_Util.hpp"

TTF_Font *font = nullptr;
float SCALE_X = 0, SCALE_Y = 0;

void drawText(SDL_Renderer *renderer, const char *text, int color, int x, int y)
{    
    if(font == nullptr)
    {
        INFO("Font not yet initialized");
        return;
    }
        
    SDL_Surface *srfc = TTF_RenderText_Solid(font, text, TO_COLOR(color)); // rgba
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, srfc);
    if(text)
    {
        SDL_Rect dst = {x, y, srfc->w, srfc->h};
        SDL_RenderCopy(renderer, texture, NULL, &dst);
    }
    SDL_FreeSurface(srfc);
    SDL_DestroyTexture(texture);
}

void drawTextAspect(SDL_Renderer *renderer, const char *text, int color, int x, int y, int w, int h)
{
    if(font == nullptr)
    {
        INFO("Font not yet initialized");
        return;
    }
    
    SDL_Surface *srfc = TTF_RenderText_Solid(font, text, TO_COLOR(color));
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, srfc);
    if(texture == nullptr) return;
    
    if(text)
    {
        float scaleX = SCALE_X * (float) w / (float) srfc->w;
        float scaleY = SCALE_Y * (float) h / (float) srfc->h;
        float scale = (float) fmin(scaleX, scaleY); // Smaller scale value
        
        SDL_Rect dst = {(int)(x * SCALE_X / scale), (int)(y * SCALE_Y / scale), srfc->w, srfc->h}; // Desination rect
        SDL_RenderSetScale(renderer, scale, scale); // Set scaling
        SDL_RenderCopy(renderer, texture, NULL, &dst); // Render stuff
        SDL_RenderSetScale(renderer, SCALE_X, SCALE_Y); // Reset scale
    }
    
    // Clean up
    SDL_FreeSurface(srfc);
    SDL_DestroyTexture(texture);
}

void drawTextCentered(SDL_Renderer *renderer, const char *text, int color, int x, int y, int w, int h)
{
    int textwidth, textheight;
    TTF_SizeText(font, text, &textwidth, &textheight);
    
    x += (w - textwidth) / 2;
    w = textwidth;
    y += (h - textheight) / 2;
    h = textheight;
    
    if(font == nullptr)
    {
        INFO("Font not yet initialized");
        return;
    }
    
    SDL_Surface *srfc = TTF_RenderText_Solid(font, text, TO_COLOR(color));
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, srfc);
    if(texture == nullptr) return;
    
    if(text)
    {
        float scaleX = SCALE_X * (float) w / (float) srfc->w;
        float scaleY = SCALE_Y * (float) h / (float) srfc->h;
        float scale = (float) fmin(scaleX, scaleY); // Smaller scale value
        
        SDL_Rect dst = {(int)(x * SCALE_X / scale), (int)(y * SCALE_Y / scale), srfc->w, srfc->h}; // Desination rect
        SDL_RenderSetScale(renderer, scale, scale); // Set scaling
        SDL_RenderCopy(renderer, texture, NULL, &dst); // Render stuff
        SDL_RenderSetScale(renderer, SCALE_X, SCALE_Y); // Reset scale
    }
    
    // Clean up
    SDL_FreeSurface(srfc);
    SDL_DestroyTexture(texture);
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
        case SDL_SCANCODE_BACKSPACE:
            return '\x08';
        case SDL_SCANCODE_SPACE:
            return ' ';
        case SDL_SCANCODE_LSHIFT: // No characters for this key
        case SDL_SCANCODE_RSHIFT:
        case SDL_SCANCODE_CAPSLOCK:
        case SDL_SCANCODE_TAB:
        case SDL_SCANCODE_LALT:
        case SDL_SCANCODE_RALT:
            return '\0';
        default:
            return '?'; // Unknown char
    }
}
