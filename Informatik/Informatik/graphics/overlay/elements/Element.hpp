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

class Element
{
protected:
    // Helper functions like draw circles or draw text?
    
public:
    virtual void render(SDL_Renderer *renderer) = 0;
    virtual void processEvent(SDL_Event e) = 0; // Like update, but with all events like mouse
};

#endif /* Element_hpp */
