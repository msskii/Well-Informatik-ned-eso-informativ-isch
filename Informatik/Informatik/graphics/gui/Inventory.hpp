//
//  Inventory.hpp
//  Informatik
//
//  Created by Aaron Hodel on 06.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Inventory_hpp
#define Inventory_hpp

#include "../overlay/Menu.hpp"

class Inventory : public Menu
{
public:
    Inventory(Player *p);
    
    bool shouldWindowClose() override;
    void renderMenu(SDL_Renderer *renderer) override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* Inventory_hpp */
