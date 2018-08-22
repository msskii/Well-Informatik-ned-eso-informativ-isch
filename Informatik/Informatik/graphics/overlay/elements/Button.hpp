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

class Button : public Element
{
protected:
    int x, y, w, h;
    bool hoverOver = false;
    bool clicked = false;
    
public:
    Button(int x, int y, int w, int h);
    void render(SDL_Renderer *renderer) override;
    void processEvent(SDL_Event e) override;
};

#endif /* Button_hpp */
