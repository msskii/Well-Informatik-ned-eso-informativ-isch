//
//  Button.hpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

#include "Element.hpp"

typedef void (*buttonClickHandler)(Menu *menu, int bID);
static int buttonIDCounter = 0;

class Button : public Element
{
protected:
    int x, y, w, h;
    bool hoverOver = false;
    bool clicked = false;
    int id = buttonIDCounter++;
    
    buttonClickHandler handler;
    
public:
    Button(buttonClickHandler bhandler, int x, int y, int w, int h);
    Button(buttonClickHandler bhandler, int x, int y, int w, int h, int id);

    void render(SDL_Renderer *renderer) override;
    void processEvent(Menu *menu, SDL_Event e) override;
};

#endif /* Button_hpp */
