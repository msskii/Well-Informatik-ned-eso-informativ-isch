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

public:
    const char *text;
    Text(const char *text, int x, int y, int w, int h);
    
    void render() override;
    void processEvent(Menu *menu, SDL_Event e) override;
};


class DebugText;
typedef const char* (*textUpdate)(Menu *menu, DebugText *text);

class DebugText : public Element
{
public:
    textUpdate updater;
    const char *format;
    int maxLength;
    char *buffer;
        
public:
    DebugText(const char* format, int ml, textUpdate updater, int x, int y, int w, int h, int id);
    
    void render() override;
    void processEvent(Menu *menu, SDL_Event e) override;
};

#endif /* Text_hpp */
