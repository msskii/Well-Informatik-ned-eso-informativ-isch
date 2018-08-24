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

class DebugOverlay : public Menu
{
protected:
    Level *level;
    
public:
    DebugOverlay(Level *level);
    
    bool shouldWindowClose();
    void renderMenu(SDL_Renderer *renderer);
    void updateMenu(const uint8_t *keys);
    void onOpen();
    void onClose();
};

#endif /* DebugOverlay_hpp */
