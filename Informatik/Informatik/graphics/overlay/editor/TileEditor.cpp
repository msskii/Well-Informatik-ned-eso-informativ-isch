//
//  TileEditor.cpp
//  Informatik
//
//  Created by Aaron Hodel on 29.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "TileEditor.hpp"

void variantSliderCallback(Menu *menu, int variant)
{
    TileEditor *m = (TileEditor*) menu;
    m->level->tiles[m->tileID].data.variant = variant;
    m->level->tiles[m->tileID].reloadTexture(variant);
}

void tilenumberCallback(Menu *menu, DropDownElement tile)
{
    TileEditor *m = (TileEditor*) menu;
    m->level->tiles[m->tileID].data.tileNumber = tile.id;
    m->level->tiles[m->tileID].reloadTexture(m->level->tiles[m->tileID].data.variant);
}

TileEditor::TileEditor(Level* level, int tid) : tileID(tid)
{
    Tile t = level->tiles[tid];
    this->level = level;
    
    zheight_slider = new Slider(0, 0xFF, t.data.tileZ, 0, 000, 500, 100, 0);
    addElement(zheight_slider);
    
    variant_slider = new Slider(0, 100, t.data.variant, 0, 100, 500, 100, 0);
    variant_slider->setCallback(variantSliderCallback);
    addElement(variant_slider);
    
    tilenumber_dropdown = new DropDown(t.data.tileNumber, 0, 200, 500, 100, 0);
    tilenumber_dropdown->setCallback(tilenumberCallback);
    // tilenumber_dropdown->toTheRight = true;
    tilenumber_dropdown->addOption(0, "0: Grass");
    tilenumber_dropdown->addOption(1, "1: Stonepath");
    addElement(tilenumber_dropdown);
}

void TileEditor::switchSide()
{
    int toAdd = GAME_WIDTH - 600;
    toAdd *= isOnLeftSide ? 1 : -1;
    
    for(int i = 0; i < (int) elements.size(); i++) elements[i]->x += toAdd;
    isOnLeftSide = !isOnLeftSide;
}

bool TileEditor::shouldWindowClose() { return false; }

void TileEditor::renderMenu(SDL_Renderer *renderer)
{
    SDL_Rect background = {isOnLeftSide ? 0 : GAME_WIDTH - 600, 0, 600, GAME_HEIGHT};
    COLOR(renderer, 0x55FFFFFF);
    SDL_RenderFillRect(renderer, &background);
}

void TileEditor::updateMenu(const uint8_t *keys)
{
    if(keys[SDL_SCANCODE_RETURN])
    {
        menuShouldBeClosed = true;
    }
    
    if(keys[SDL_SCANCODE_J])
    {
        if(!jpressed)
        {
            switchSide();
        }
        jpressed = true;
    } else jpressed = false;
}

void TileEditor::onOpen() {}
void TileEditor::onClose()
{
    level->tiles[tileID].data.tileNumber = tilenumber_dropdown->currentID;
    level->tiles[tileID].data.tileZ = zheight_slider->currentValue;
    level->tiles[tileID].data.variant = variant_slider->currentValue;
    level->tiles[tileID].reloadTexture(level->tiles[tileID].data.variant);
}

