//
//  EditorOverlay.hpp
//  Informatik
//
//  Created by Aaron Hodel on 29.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef EditorOverlay_hpp
#define EditorOverlay_hpp

#include "../Menu.hpp"

// Custom element to handle mouse events
class EditorClickHandler : public Element
{
private:
    
public:
    EditorClickHandler();
    
    void render(SDL_Renderer *renderer) override;
    void processEvent(Menu *menu, SDL_Event e) override;
};

class EditorOverlay : public Menu
{
public:
    EditorOverlay();
    
    bool shouldWindowClose() override;
    void renderMenu(SDL_Renderer *renderer) override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* EditorOverlay_hpp */
