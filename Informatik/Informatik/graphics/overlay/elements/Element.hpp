//
//  Element.hpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Element_hpp
#define Element_hpp

#include "../../../util/SDL_Util.hpp"

class Menu;

class Element // Full definition of the element class, as used by the menus
{
protected:
    // Helper functions like draw circles or draw text?
    Menu *menu;

public:
	int elementID;
    bool consumeEvent = false;

    void addToMenu(Menu *menu);
    
    virtual void render(SDL_Renderer *renderer) = 0;
    virtual void processEvent(Menu *menu, SDL_Event e) = 0; // Like update, but with all events like mouse
};

// #include "../Menu.hpp" // Full definition of the Menu class, as used by the other elements

#endif /* Element_hpp */
