//
//  Menu.hpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Menu_hpp
#define Menu_hpp

#include "../../util/SDL_Util.hpp"
#include "../../util/Logger.hpp"

#include "elements/Elements.hpp"
#include <vector>

class Menu // Basic menu class to extend from
{
protected:
    std::vector<Element*> elements;
public:
    bool active = false; // Currently active?
    Menu *under = nullptr; // The menu that is under this one, so we can close one menu and go back to the last
    bool menuShouldBeClosed = false; // Used to close menus apart from the shouldwindowclose method
    
    void addElement(Element *e);
    
public:
    void render(SDL_Renderer *renderer, const uint8_t *keys);
    void openSubMenu(Menu *menu);
    void open();
    void close();
    void updateElements(SDL_Event e);
    
    // Functions to override
    virtual bool shouldWindowClose() = 0;
    virtual void renderMenu(SDL_Renderer *renderer) = 0;
    virtual void updateMenu(const uint8_t *keys) = 0;
    virtual void onOpen() = 0;
    virtual void onClose() = 0;
};

#endif /* Menu_hpp */
