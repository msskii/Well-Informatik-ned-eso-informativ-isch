//
//  EventCreateMenu.hpp
//  Informatik
//
//  Created by Aaron Hodel on 24.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef EventCreateMenu_hpp
#define EventCreateMenu_hpp

#include "../elements/Elements.hpp"
#include "../Menu.hpp"
#include <string>
#include <stdint.h>

class EventCreateMenu : public Menu
{
public:
    Slider *x_slider, *y_slider, *w_slider, *h_slider;
    Slider *amount_slider, *id_slider, *dependency_slider;
    
    DropDown *actions, *type_filter;
    uint8_t *arguments;
    bool jpressed, isOnLeftSide = true;
    
public:
    EventCreateMenu();
	EventCreateMenu(Event *defaults);
    
    Slider **argumentSliders;
    int argumentCount = 0;
    void updateArguments();

    void switchSide();
    
    bool shouldWindowClose() override;
    void renderMenu(SDL_Renderer *renderer) override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* EventCreateMenu_hpp */
