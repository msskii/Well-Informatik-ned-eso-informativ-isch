//
//  PopupText.hpp
//  Informatik
//
//  Created by Aaron Hodel on 04.12.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef PopupText_hpp
#define PopupText_hpp

#include "Menu.hpp"

class PopupText : public Menu
{
private:
    const char* text;
    int decayTimer, maxDecay;
    cachedTexture texture;
    
public:
    PopupText(const char* text, int timeInFrames);
    
    // Functions to override
    bool shouldWindowClose() { return decayTimer <= 0; }
    void renderMenu();
    void updateMenu(const uint8_t *keys) {}
    void onOpen() {}
    void onClose() {}
};

#endif /* PopupText_hpp */
