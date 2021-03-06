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
    Slider *zheight_slider, *variant_slider;
    bool isOnLeftSide = true;
    bool jpressed;
    
public:
    TileEditor(Level *level, int i);
    friend void variantSliderCallback(Menu *menu, int variant);
    friend void tilenumberCallback(Menu *menu, DropDownElement tile);
    
    void switchSide();
    
    bool shouldWindowClose() override;
    void renderMenu() override;
    void drawOverlay() override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* TileEditor_hpp */
