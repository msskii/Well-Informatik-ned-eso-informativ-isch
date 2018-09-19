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
#include <map>

class Menu;

#define NUM_TEXTURES 7
enum ElementTextureNames
{
    BUTTON_NORMAL = 0,
    BUTTON_HOVER,
    BUTTON_CLICKED,
    DROPDOWN,
    DROPDOWN_ELEMENT,
    DROPDOWN_ELEMENT_HOVER,
    TEXTBOX
};

static const char** texturePaths = new const char*[NUM_TEXTURES]
{
    "/elements/button_normal",
    "/elements/button_hover",
    "/elements/button_clicked",
    "/elements/dropdown",
    "/elements/dropdown_element",
    "/elements/dropdown_element_hover",
    "/elements/textbox"
};

// extern std::map<int, SDL_Texture*> textures;
extern std::map<int, gl_texture> gl_textures;
extern void reloadElementTextures(SDL_Renderer *renderer);

class Element // Full definition of the element class, as used by the menus
{
protected:
    // Helper functions like draw circles or draw text?
    Menu *menu;

public:
	int elementID;
    int x, y, w, h;
    bool consumeEvent = false;

    void addToMenu(Menu *menu);
    
    virtual void render(SDL_Renderer *renderer) = 0;
    virtual void processEvent(Menu *menu, SDL_Event e) = 0; // Like update, but with all events like mouse
};

// #include "../Menu.hpp" // Full definition of the Menu class, as used by the other elements

#endif /* Element_hpp */
