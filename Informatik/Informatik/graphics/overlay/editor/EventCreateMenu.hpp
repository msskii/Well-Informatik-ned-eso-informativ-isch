//
//  EventCreateMenu.hpp
//  Informatik
//
//  Created by Aaron Hodel on 24.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef EventCreateMenu_hpp
#define EventCreateMenu_hpp

#include "../Menu.hpp"
#include <string>
#include <stdint.h>

class EventCreateMenu : public Menu
{
public:
    EventCreateMenu();
    
    bool shouldWindowClose() override;
    void renderMenu(SDL_Renderer *renderer) override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* EventCreateMenu_hpp */
