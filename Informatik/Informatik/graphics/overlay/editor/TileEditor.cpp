//
//  TileEditor.cpp
//  Informatik
//
//  Created by Aaron Hodel on 29.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "TileEditor.hpp"

TileEditor::TileEditor(Level* level, int tid) : tileID(tid)
{
    Tile t = level->tiles[tid];
    this->level = level;
    
    zheight_slider = new Slider(0, 0xFF, t.data.tileZ, 0, 000, 500, 100, 0);
    addElement(zheight_slider);
    
    variant_slider = new Slider(0, 100, t.data.variant, 0, 100, 500, 100, 0);
    addElement(variant_slider);
    
    tilenumber_dropdown = new DropDown(t.data.tileNumber, 0, 200, 500, 100, 0);
    // tilenumber_dropdown->toTheRight = true;
    tilenumber_dropdown->addOption(0, "0: Grass");
    tilenumber_dropdown->addOption(1, "1: Stonepath");
    addElement(tilenumber_dropdown);
}

bool TileEditor::shouldWindowClose() { return false; }

void TileEditor::renderMenu(SDL_Renderer *renderer)
{
    SDL_Rect background = {0, 0, 600, GAME_HEIGHT};
    COLOR(renderer, 0x55FFFFFF);
    SDL_RenderFillRect(renderer, &background);
}

void TileEditor::updateMenu(const uint8_t *keys)
{
    if(keys[SDL_SCANCODE_RETURN])
    {
        menuShouldBeClosed = true;
    }
}

void TileEditor::onOpen() {}
void TileEditor::onClose()
{
    level->tiles[tileID].data.tileNumber = tilenumber_dropdown->currentID;
    level->tiles[tileID].data.tileZ = zheight_slider->currentValue;
    level->tiles[tileID].data.variant = variant_slider->currentValue;
    level->tiles[tileID].reloadTexture(level->tiles[tileID].data.variant);
}

