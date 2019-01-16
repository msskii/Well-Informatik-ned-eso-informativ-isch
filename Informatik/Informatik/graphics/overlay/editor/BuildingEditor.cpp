//
//  BuildingEditor.cpp
//  Informatik
//
//  Created by Aaron Hodel on 18.12.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "BuildingEditor.hpp"

BuildingEditor::BuildingEditor(Level *lvl, int bid) : level(lvl), buildingID(bid)
{
    
}

bool BuildingEditor::shouldWindowClose() { return false; }
void BuildingEditor::renderMenu() {}
void BuildingEditor::drawOverlay() {}
void BuildingEditor::updateMenu(const uint8_t *keys) {}
void BuildingEditor::onOpen() {}
void BuildingEditor::onClose() {}
