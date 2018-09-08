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
#include "ItemSlot.hpp"

class Inventory : public Menu
{
public:
    Inventory(Player *p);
    Player *player;
    
    ItemSlot *selected = nullptr;
    int hoverX, hoverY;
    
    bool shouldWindowClose() override;
    void renderMenu(SDL_Renderer *renderer) override;
    void drawOverlay(SDL_Renderer *renderer) override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* Inventory_hpp */
