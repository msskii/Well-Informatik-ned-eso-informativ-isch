//
//  Shop.cpp
//  Informatik
//
//  Created by Aaron Hodel on 02.11.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Shop.hpp"

Shop::Shop(const char *path, int money, std::vector<shopItem> stock)
{
    inStock = stock;
    currentMoney = money;
    background_surface = IMG_Load(GET_TEXTURE_PATH((std::string("/backgrounds/") + path).c_str()));
    
    for(size_t i = 0; i < inStock.size(); i++)
    {
        stockNameTextures.push_back({});
        inStock[i].item.updateTexture();
    }
    
    selectedInfo.push_back({});
    selectedInfo.push_back({});
    selectedInfo.push_back({});
    selectedInfo.push_back({});
    selectedInfo.push_back({});
}

bool Shop::shouldWindowClose() { return false; }

void Shop::renderMenu()
{
    for(size_t i = 0; i < inStock.size(); i++)
    {
        if(i == selected) continue;
        
        renderWithoutShading(inStock[i].item.texture, {}, {1244, 40 + (int) i * 100, 100, 100});
        drawTextAspect(inStock[i].item.name, 0xFF000000, {1344, 40 + (int) i * 100, 500, 100}, stockNameTextures[i], update);
    }
    
    if(selected >= inStock.size()) return;
    
    renderWithoutShading(inStock[selected].item.texture, {}, {1244, 40 + selected * 100, 100, 100});
    drawTextAspect(inStock[selected].item.name, 0xFFFFFFFF, {1344, 40 + selected * 100, 500, 100}, stockNameTextures[selected], update);
    
    renderWithoutShading(inStock[selected].item.texture, {}, {640, 230, 100, 100});
    drawTextAspect(inStock[selected].item.name, 0xFFFFFFFF, {740, 230, 500, 100}, stockNameTextures[selected], update);
    
    drawTextAspect(std::to_string(inStock[selected].stock).c_str(), 0xFF000000, {1010, 300, 500, 100}, selectedInfo[0], update);
    drawTextAspect(std::to_string(inStock[selected].buyPrice).c_str(), 0xFF000000, {1010, 400, 500, 100}, selectedInfo[1], update);
    drawTextAspect(std::to_string(inStock[selected].sellPrice).c_str(), 0xFF000000, {1010, 500, 500, 100}, selectedInfo[2], update);
    
    drawTextAspect(std::to_string(currentMoney).c_str(), 0xFF000000, {1000, 60, 200, 100}, selectedInfo[3], update);

    drawTextAspect("Buy menu test", 0xFF000000, {40, 790, 1160, 100}, selectedInfo[4], update);
    
    update = false;
}

void Shop::updateMenu(const uint8_t *keys)
{
    int x, y;
    bool pressed = SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT);
    
    x /= SCALE_X;
    y /= SCALE_Y;
    if(x >= 1244 && x <= 1880)
    {
        selected = (y - 40) / 100;
        if(selected < 0 || selected >= inStock.size()) selected = 0;
        update = true;
    }
    
    if(cooldown)
    {
        --cooldown;
        if(!keys[SDL_SCANCODE_DOWN] && !keys[SDL_SCANCODE_UP]) cooldown = 0;
        return;
    }
    
    if(pressed && !lastPressed && currentMoney >= inStock[selected].buyPrice && inStock[selected].stock > 0)
    {
        currentMoney -= inStock[selected].buyPrice;
        --inStock[selected].stock;
        window->level->getLocalPlayer()->addItem(&inStock[selected].item);
        update = true;
    }
    lastPressed = pressed;

    if(keys[SDL_SCANCODE_DOWN])
    {
        if(selected < (int) inStock.size() - 1) ++selected;
        update = true;
        cooldown = 10;
    }
    else if(keys[SDL_SCANCODE_UP])
    {
        if(selected > 0) --selected;
        update = true;
        cooldown = 10;
    }
    
    if(keys[SDL_SCANCODE_RETURN]) menuShouldBeClosed = true;
}

void Shop::onOpen() {}
void Shop::onClose() {}
