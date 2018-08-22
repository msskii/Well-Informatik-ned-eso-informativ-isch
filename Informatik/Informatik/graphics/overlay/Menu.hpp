//
//  Menu.hpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Menu_hpp
#define Menu_hpp

#ifdef __APPLE__
#  include <SDL2/SDL.h> // Other path than on windows
#else
#  include <SDL2.h>
#endif

class Menu // Basic menu class to extend from
{
protected:
    bool active = false; // Currently active?
    
public:
    void render();
    
    // Functions to override
    virtual bool shouldWindowClose() = 0;
    virtual void renderMenu() = 0;
    virtual void updateMenu(uint8_t *keys) = 0;
};

#endif /* Menu_hpp */
