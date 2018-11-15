//
//  Shop.cpp
//  Informatik
//
//  Created by Aaron Hodel on 02.11.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Shop.hpp"

Shop::Shop(const char *path, int money, std::vector<Item> stock)
{
    inStock = stock;
    currentMoney = money;
    background_surface = IMG_Load(GET_TEXTURE_PATH((std::string("/backgrounds/") + path).c_str()));
    
    for(size_t i = 0; i < inStock.size(); i++) stockNameTextures.push_back({});
}

bool Shop::shouldWindowClose() { return false; }

void Shop::renderMenu()
{
    for(size_t i = 0; i < inStock.size(); i++)
    {
        renderWithShading(inStock[i].texture, {}, {0, (int) i * 100, 100, 100});
        drawTextAspect(inStock[i].name, 0xFF000000, {100, (int) i * 100, 500, 100}, stockNameTextures[i], false);
    }
    
    renderWithShading(inStock[selected].texture, {}, {0, selected * 100, 100, 100});
    drawTextAspect(inStock[selected].name, 0xFFFFFFFF, {100, selected * 100, 500, 100}, stockNameTextures[selected], true);
}

void Shop::updateMenu(const uint8_t *keys)
{
    if(keys[SDL_SCANCODE_DOWN])
    {
        if(selected < (int) inStock.size() - 1) ++selected;
    }
    else if(keys[SDL_SCANCODE_UP])
    {
        if(selected > 0) --selected;
    }
}

void Shop::onOpen() {}
void Shop::onClose() {}
