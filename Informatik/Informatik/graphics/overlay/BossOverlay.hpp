//
//  BossOverlay.hpp
//  Informatik
//
//  Created by Aaron Hodel on 04.12.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef BossOverlay_hpp
#define BossOverlay_hpp

#include "Menu.hpp"

class BossOverlay : public Menu
{
private:
    const char* bossName;
    
public:
    BossOverlay(const char *name) : bossName(name) { shouldLevelBeUpdated = true; }
    
    bool shouldWindowClose() { return false; }
    void renderMenu();
    void updateMenu(const uint8_t *keys) {}
    void onOpen() {}
    void onClose() {}
};

#endif /* BossOverlay_hpp */
