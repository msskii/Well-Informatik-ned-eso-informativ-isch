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
    GLfloat *positions = new float[3 * MAX_LIGHTS];
    
public:
    LightOverlay();
    
    bool shouldWindowClose() override;
    void renderMenu() override;
    void drawOverlay() override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* LightOverlay_hpp */
