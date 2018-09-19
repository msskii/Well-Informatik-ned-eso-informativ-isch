//
//  MainMenu.hpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef MainMenu_hpp
#define MainMenu_hpp

#include "Menu.hpp"
#include "editor/EditorOverlay.hpp"
#include "../../config/ConfigMenu.hpp"
#include "../../multiplayer/Server.hpp"

class MainMenu : public Menu
{
protected:
    bool gameStart = false;
    
public:
    MainMenu();
    
    bool shouldWindowClose() override;
    void renderMenu() override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* MainMenu_hpp */
