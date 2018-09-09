//
//  DialogOverlay.hpp
//  Informatik
//
//  Created by Aaron Hodel on 27.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef DialogOverlay_hpp
#define DialogOverlay_hpp

#include "Menu.hpp"

class DialogOverlay : public Menu
{
private:
    bool dialogOver = false;
    int timeout = 0;
    std::string text;
    
public:
    DialogOverlay(const char *t);
    
    bool shouldWindowClose() override;
    void renderMenu(SDL_Renderer *renderer) override;
    void drawOverlay(SDL_Renderer *renderer) override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* DialogOverlay_hpp */
