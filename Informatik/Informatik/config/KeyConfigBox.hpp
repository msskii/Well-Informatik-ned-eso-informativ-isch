//
//  KeyConfigBox.hpp
//  Informatik
//
//  Created by Aaron Hodel on 25.10.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef KeyConfigBox_hpp
#define KeyConfigBox_hpp

#include "../graphics/overlay/elements/TextBox.hpp"

class KeyConfigBox : public TextBox
{
public:
    KeyConfigBox(SDL_Keycode code, int x, int y, int w, int h, int id);
    void processEvent(Menu *menu, SDL_Event e) override;
    
    std::string toStore = "";
};

#endif /* KeyConfigBox_hpp */
