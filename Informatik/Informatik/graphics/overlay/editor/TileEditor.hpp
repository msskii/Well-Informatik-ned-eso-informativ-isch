//
//  TileEditor.hpp
//  Informatik
//
//  Created by Aaron Hodel on 29.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef TileEditor_hpp
#define TileEditor_hpp

#include "../Menu.hpp"

class TileEditor : public Menu
{
protected:
    int tileID;
    Level *level;
    
    DropDown *tilenumber_dropdown;
    
public:
    TileEditor(Level *level, int i);
    
    bool shouldWindowClose() override;
    void renderMenu(SDL_Renderer *renderer) override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* TileEditor_hpp */
