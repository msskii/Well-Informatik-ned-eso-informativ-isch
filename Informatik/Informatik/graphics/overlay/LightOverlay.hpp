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

#define MAX_LIGHTS 40

class LightOverlay : public Menu
{
private:
    GLuint shader_id;
    GLfloat *positions = new float[2 * MAX_LIGHTS];
    
public:
    LightOverlay(GLuint id);
    
    bool shouldWindowClose() override;
    void renderMenu(SDL_Renderer *renderer) override;
    void drawOverlay(SDL_Renderer *renderer) override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* LightOverlay_hpp */
