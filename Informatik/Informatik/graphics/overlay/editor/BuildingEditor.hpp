//
//  BuildingEditor.hpp
//  Informatik
//
//  Created by Aaron Hodel on 18.12.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef BuildingEditor_hpp
#define BuildingEditor_hpp

#include "../Menu.hpp"

class BuildingEditor : public Menu
{
protected:
    int buildingID;
    Level *level;
    
    DropDown *building_dropdown;
    
public:
    BuildingEditor(Level *level, int buildingIndex);
    
    bool shouldWindowClose() override;
    void renderMenu() override;
    void drawOverlay() override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};
#endif /* BuildingEditor_hpp */
