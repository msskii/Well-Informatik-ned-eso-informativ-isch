//
//  Text.hpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Text_hpp
#define Text_hpp

#include "Element.hpp"

class Text : public Element
{
protected:
    int x, y, w, h;
    const char *text;

public:
    
    Text(const char *text, int x, int y, int w, int h);
    
    void render(SDL_Renderer *renderer) override;
    void processEvent(Menu *menu, SDL_Event e) override;
};

#endif /* Text_hpp */