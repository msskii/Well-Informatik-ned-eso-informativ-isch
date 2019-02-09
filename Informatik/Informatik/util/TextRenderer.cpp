//
//  TextRenderer.cpp
//  Informatik
//
//  Created by Aaron Hodel on 09.02.19.
//  Copyright © 2019 Aaron Hodel. All rights reserved.
//

#include "TextRenderer.hpp"

gl_texture *char_textures = new gl_texture[0x60]; // We have 0x60 drawable characters (From 0x20 to 0x7F)

void setupTextRenderer(const char *fontFile) // Load all characters
{
    TTF_Font *font = TTF_OpenFont(fontFile, FONT_RESOLUTION);
    SDL_Surface *surface;
    for(uint8_t c = 0x20; c < 0x7F; c++)
    {
        // printf("Creating texture for character %c\n", c);
        surface = TTF_RenderGlyph_Solid(font, c, {0xFF, 0xFF, 0xFF, 0xFF});
        if(surface)
        {
            if(surface->format->format != SDL_PIXELFORMAT_ARGB8888)
            {
                SDL_Surface *correctFormat = SDL_CreateRGBSurfaceWithFormat(0, surface->clip_rect.w, surface->clip_rect.h, 32, SDL_PIXELFORMAT_ARGB8888);
                if(!correctFormat)
                {
                    printf("[ERROR] Couldn't create correct pixelformat\n");
                    continue;
                }
                SDL_SetSurfaceBlendMode(correctFormat, SDL_BLENDMODE_BLEND);
                SDL_BlitSurface(surface, NULL, correctFormat, NULL);
                SDL_FreeSurface(surface);
                surface = correctFormat; // Set the surface to the correct one...
            }
            
            char_textures[c - 0x20] = getTexture(surface);
        }
        else printf("[ERROR] Error creating the surface for character: %c: Couldn't render character\n", c);
    }
}

void drawText(const char *text, SDL_Rect dst, bool centered) // Draw text --> No colors here! (Just white text)
{
    int renderWidth = 0, renderHeight = 0xFFFFFFFF;
    size_t tlen = strlen(text);
    for(int i = 0; i < (int) tlen; i++)
    {
        uint8_t c = text[i];
        if(c < 0x20 || c >= 0x7F) continue; // Not rendered?
        renderWidth += char_textures[c - 0x20].width;
        renderHeight = max(renderHeight, char_textures[c - 0x20].height);
    }
    
    float factor = fmin((float) dst.w / (float) renderWidth, (float) dst.h / (float) renderHeight);
    
    float xoff = ((float) dst.w - factor * (float) renderWidth) / 2.0f;
    float yoff = ((float) dst.h - factor * (float) renderHeight) / 2.0f;

    SDL_Rect dest = {dst.x + (int) xoff, dst.y + (int) yoff, 0, 0};
    for(int i = 0; i < (int) tlen; i++)
    {
        uint8_t c = text[i];
        if(c < 0x20 || c >= 0x7F) continue; // Not rendered?
        
        gl_texture texture = char_textures[c - 0x20];
        dest.w = (int)((float) texture.width * factor);
        dest.h = (int)((float) texture.height * factor);
        render(texture, {}, dest, const_shader);
        dest.x += dest.w;
    }
}

void drawTextAspect(const char *text, uint32_t color, SDL_Rect dst, cachedTexture &texture_cache, bool forceUpdate)
{
    glUseProgram(const_shader);
    glUniform4f(glGetUniformLocation(const_shader, "col_mod"), (float) ((color >> 24) & 0xFF) / 255.0f, ((color >> 16) & 0xFF) / 255.0f, ((color >> 8) & 0xFF) / 255.0f, (color & 0xFF) / 255.0f);
    drawText(text, dst, false);
    glUseProgram(const_shader);
    glUniform4f(glGetUniformLocation(const_shader, "col_mod"), 1, 1, 1, 1);
}

void drawTextCentered(const char *text, uint32_t color, SDL_Rect dst, cachedTexture &texture_cache, bool forceUpdate)
{
    glUseProgram(const_shader);
    glUniform4f(glGetUniformLocation(const_shader, "col_mod"), (float) ((color >> 24) & 0xFF) / 255.0f, ((color >> 16) & 0xFF) / 255.0f, ((color >> 8) & 0xFF) / 255.0f, (color & 0xFF) / 255.0f);
    drawText(text, dst, true);
    glUseProgram(const_shader);
    glUniform4f(glGetUniformLocation(const_shader, "col_mod"), 1, 1, 1, 1);
}
