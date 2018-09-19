//
//  DebugOverlay.hpp
//  Informatik
//
//  Created by Aaron Hodel on 24.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef DebugOverlay_hpp
#define DebugOverlay_hpp

#include "Menu.hpp"
#include "../../level/Level.hpp"
#include "editor/EventCreateMenu.hpp"

class DebugOverlay : public Menu
{
protected:
    Level *level;
    
    bool inc = false, dec = false;
    
public:
    DebugOverlay(Level *level);
    
    int eventIdCounter = 0;
    
    bool shouldWindowClose() override;
    void renderMenu() override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* DebugOverlay_hpp */
