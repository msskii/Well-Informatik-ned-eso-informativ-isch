//
//  ClientOverlay.hpp
//  Informatik
//
//  Created by Aaron Hodel on 25.10.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef ClientOverlay_hpp
#define ClientOverlay_hpp

#include "../graphics/overlay/Menu.hpp"

#define CHAT_WIDTH 600

typedef struct ChatElement
{
    Text *text = nullptr; // Text element for the menu, with the text itself
    int disappearTimer = 60 * 10; // Roughly 10 seconds?
} ChatElement;

class ClientOverlay : public Menu
{
private:
    bool lastState = false;
    TextBox *textBox = nullptr;
    bool opened = false;
    
public:
    ClientOverlay();
    
    std::vector<ChatElement> messages;
    
    void addMessage(std::string text);
    
    bool shouldWindowClose();
    void renderMenu(); // Render background of menu
    void updateMenu(const uint8_t *keys);
    void onOpen();
    void onClose();
};

#endif /* ClientOverlay_hpp */
