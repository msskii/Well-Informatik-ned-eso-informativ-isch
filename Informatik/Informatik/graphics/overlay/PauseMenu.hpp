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
    
    bool shouldWindowClose() override;
    void renderMenu(SDL_Renderer *renderer) override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* PauseMenu_hpp */
