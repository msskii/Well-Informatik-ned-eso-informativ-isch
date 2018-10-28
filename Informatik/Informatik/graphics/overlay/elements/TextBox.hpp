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
    bool focus = false; // No default focus
    bool hoverOver = false;
    float usedScale = 1.0;
    
    int selectionStart = 0;
    int currentIndex = 0;
    
    cachedTexture lastTexture;
    
public:
    bool changed = true;
    bool defaultText = true;

    TextBox(const char *defaultText, int x, int y, int w, int h, int id);
    std::string currentText;
    inline void getFocus() { focus = true; }

    void render() override;
    void processEvent(Menu *menu, SDL_Event e) override;
};


#endif /* TextBox_hpp */
