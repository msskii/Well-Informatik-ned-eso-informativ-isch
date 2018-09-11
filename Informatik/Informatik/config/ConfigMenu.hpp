//
//  ConfigMenu.hpp
//  Informatik
//
//  Created by Aaron Hodel on 10.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef ConfigMenu_hpp
#define ConfigMenu_hpp

#include "../graphics/overlay/Menu.hpp"
#include "ConfigLoader.hpp"
#include <vector>

#define SCROLL_SPEED 5

class ConfigMenu : public Menu
{
private:
    std::vector<Text*> keys;
    std::vector<TextBox*> values;
    ConfigLoader *loader;
    int scrollAmount = 0, y = 0;
    
    friend void buttonHandler(Menu *menu, Button* button);
    
public:
    ConfigMenu(ConfigLoader *loader);
    
    bool shouldWindowClose() override;
    void renderMenu(SDL_Renderer *renderer) override;
    void drawOverlay(SDL_Renderer *renderer) override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;    
};

#endif /* ConfigMenu_hpp */
