//
//  Menu.hpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Menu_hpp
#define Menu_hpp

#include "elements/Elements.hpp"
#include "../../util/SDL_Util.hpp"
#include "../../util/Logger.hpp"

#include "elements/Elements.hpp"
#include <vector>

class Window;

class Menu // Basic menu class to extend from
{
public:
    std::vector<Element*> elements;
    
public:
    bool active = false; // Currently active?
    Menu *under = nullptr; // The menu that is under this one, so we can close one menu and go back to the last
    bool menuShouldBeClosed = false; // Used to close menus apart from the shouldwindowclose method
    Window *window;
    
    gl_texture background_texture;
    SDL_Surface *background_surface = nullptr;
    
    bool shouldLevelBeUpdated = false; // Set to true for overlays like shops or minimaps
    
    Element *addElement(Element *e);
    Element *removeElement(Element *e);
    
public:
    ~Menu();
    
    template <class T>
    inline Element *getElement(int a)
    {
        for(int i = 0; i < (int)elements.size(); i++)
        {
            auto &element = *elements[i];
            if(typeid(element) == typeid(T) && elements[i]->elementID == a) return elements[i];
        }
        return nullptr;
    }
    
    void render(const uint8_t *keys);
    void openSubMenu(Menu *menu);
    void open(Window *window);
    void close();
    virtual void updateElements(SDL_Event e);

    virtual void drawOverlay();
    virtual void drawBackground();

    
    // Functions to override
    virtual bool shouldWindowClose() = 0;
    virtual void renderMenu() = 0; // Render background of menu
    virtual void updateMenu(const uint8_t *keys) = 0;
    virtual void onOpen() = 0;
    virtual void onClose() = 0;
};

#include "../Window.hpp"

#endif /* Menu_hpp */
