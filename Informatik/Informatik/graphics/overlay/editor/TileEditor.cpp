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
    
    tilenumber_dropdown = new DropDown(t.data.tileNumber, 0, 0, 500, 100, 0);
    // tilenumber_dropdown->toTheRight = true;
    tilenumber_dropdown->addOption(0, "0: Grass");
    tilenumber_dropdown->addOption(1, "1: Stonepath");
    addElement(tilenumber_dropdown);
}

bool TileEditor::shouldWindowClose() { return false; }

void TileEditor::renderMenu(SDL_Renderer *renderer)
{
    SDL_Rect dst = { (int)(tileID % window->level->width) * TILE_SIZE + (window->level->player->getOffsetX() % TILE_SIZE) + TILE_SIZE / 2, (int)(tileID / window->level->width) * TILE_SIZE + (window->level->player->getOffsetY() % TILE_SIZE) + TILE_SIZE, TILE_SIZE, TILE_SIZE };
    COLOR(renderer, 0xAFFFFFFF);
    SDL_RenderFillRect(renderer, &dst);
    
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
    level->tiles[tileID].reloadTexture();
}

