//
//  PauseMenu.hpp
//  Informatik
//
//  Created by Aaron Hodel on 02.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef PauseMenu_hpp
#define PauseMenu_hpp

#include "Menu.hpp"

class PauseMenu : public Menu
{
public:
    PauseMenu();
    
    void updateElements(SDL_Event e) override;
    
    bool shouldWindowClose() override;
    void renderMenu() override;
    void drawOverlay() override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* PauseMenu_hpp */
