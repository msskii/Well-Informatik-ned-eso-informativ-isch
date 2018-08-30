//
//  Dropdown.hpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Dropdown_hpp
#define Dropdown_hpp

#include "Element.hpp"
#include <vector>

typedef struct DropDownElement
{
    
    int id = 0;
    const char *text = nullptr;
    
} DropDownElement;

class DropDown : public Element
{
protected:
    std::vector<DropDownElement> elements;
    bool expanded = false;

public:
    int x, y, w, h;
    int currentSelected = 0;
    int currentID = 0;
    
    bool toTheRight = false;
    int currentlyOver = 0;
    
    DropDown(int defaultSelected, int x, int y, int w, int h, int id);
    
    void addOption(int index, const char *text);
    
    void render(SDL_Renderer *renderer) override;
    void processEvent(Menu *menu, SDL_Event e) override;
};

#endif /* Dropdown_hpp */
