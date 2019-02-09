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
#include "../../../config.h"
#include <vector>

typedef struct DropDownElement
{
    
    int id = 0;
    const char *text = nullptr;
    
} DropDownElement;

typedef void (*dropdownCallback)(Menu *menu, DropDownElement newSelected);

class DropDown : public Element
{
protected:
    std::vector<DropDownElement> elements;
    bool expanded = false;

    dropdownCallback clbck = nullptr;
    
public:
    int currentSelected = 0;
    int currentID = 0;
    
    bool toTheSide = false;
    int currentlyOver = 0;
    
    DropDown(int defaultSelected, int x, int y, int w, int h, int id);
    
    void addOption(int index, const char *text);
    
    inline void setCallback(dropdownCallback c) { clbck = c; }
    void render() override;
    void processEvent(Menu *menu, SDL_Event e) override;
};

#endif /* Dropdown_hpp */
