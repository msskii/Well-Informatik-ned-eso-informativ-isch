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

class ConfigMenu : public Menu
{
private:
    
    
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
