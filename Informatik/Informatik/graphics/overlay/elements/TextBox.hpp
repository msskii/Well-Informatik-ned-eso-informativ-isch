//
//  TextBox.hpp
//  Informatik
//
//  Created by Aaron Hodel on 24.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef TextBox_hpp
#define TextBox_hpp

#include "Element.hpp"
#include <string>

class TextBox : public Element
{
protected:
    int x, y, w, h;
    
    bool defaultText = true;
    bool focus = false; // No default focus
    bool hoverOver = false;
    
public:
    TextBox(const char *defaultText, int x, int y, int w, int h, int id);
    std::string currentText;

    void render(SDL_Renderer *renderer) override;
    void processEvent(Menu *menu, SDL_Event e) override;
};


#endif /* TextBox_hpp */
