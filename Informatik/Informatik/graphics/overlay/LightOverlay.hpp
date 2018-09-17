//
//  LightOverlay.hpp
//  Informatik
//
//  Created by Aaron Hodel on 17.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef LightOverlay_hpp
#define LightOverlay_hpp

#include "Menu.hpp"

class LightOverlay : public Menu
{
private:
    GLuint compileShader(const char *path, GLenum shaderType);
    
public:
    LightOverlay(SDL_Renderer *renderer);
    
    bool shouldWindowClose() override;
    void renderMenu(SDL_Renderer *renderer) override;
    void drawOverlay(SDL_Renderer *renderer) override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* LightOverlay_hpp */
