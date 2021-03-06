//
//  Shop.cpp
//  Informatik
//
//  Created by Aaron Hodel on 02.11.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Shop.hpp"
#include "../../config/Language.hpp"

Shop::Shop(const char *path, int money, std::vector<shopItem> stock)
{
    inStock = stock;
    currentMoney = money;
    background_surface = IMG_Load(GET_TEXTURE_PATH((std::string("/backgrounds/") + path).c_str()));
    
    for(size_t i = 0; i < inStock.size(); i++)
    {
        inStock[i].buyPrice = itemData->getItemBuyValue(inStock[i].item->name);
        inStock[i].sellPrice = itemData->getItemSellValue(inStock[i].item->name);
        inStock[i].item->updateTexture();
    }
}

Shop::Shop(const char *path, int money, Player *player)
{
    currentMoney = money;
    background_surface = IMG_Load(GET_TEXTURE_PATH((std::string("/backgrounds/") + path).c_str()));

    for(int i = 0; i < (int) player->playerItems.size(); i++)
    {
        if(!player->playerItems[i].item) continue;
        inStock.push_back({player->playerItems[i].item, player->playerItems[i].amountItems}); // TODO: item values lookup
        inStock[i].item->updateTexture();
        inStock[i].buyPrice = itemData->getItemBuyValue(inStock[i].item->name);
        inStock[i].sellPrice = itemData->getItemSellValue(inStock[i].item->name);
    }
    
    selling = true;
}

bool Shop::shouldWindowClose() { return false; }

void Shop::renderMenu()
{
    for(size_t i = 0; i < inStock.size(); i++)
    {
        if(i == selected) continue;
        
        renderWithoutShading(inStock[i].item->texture, {0, 0, inStock[i].item->texture_width, inStock[i].item->texture_height}, {1244, 40 + (int) i * 100, 100, 100});
        drawTextAspect(inStock[i].item->localizedName, 0xFF000000, {1344, 40 + (int) i * 100, 500, 100});
    }
    
    if(selected >= (int) inStock.size()) return;
        
    renderWithoutShading(inStock[selected].item->texture, {0, 0, inStock[selected].item->texture_width, inStock[selected].item->texture_height}, {1244, 40 + selected * 100, 100, 100});
    drawTextAspect(inStock[selected].item->localizedName, 0xFFFFFFFF, {1344, 40 + selected * 100, 500, 120});
    
    renderWithoutShading(inStock[selected].item->texture, {0, 0, inStock[selected].item->texture_width, inStock[selected].item->texture_height}, {640, 230, 100, 100});
    drawTextAspect(inStock[selected].item->localizedName, 0xFFFFFFFF, {740, 230, 500, 100});
    
    drawTextAspect(std::to_string(inStock[selected].stock).c_str(), 0xFF000000, {1010, 300, 500, 100});
    drawTextAspect(std::to_string(inStock[selected].buyPrice).c_str(), 0xFF000000, {1010, 400, 500, 100});
    drawTextAspect(std::to_string(inStock[selected].sellPrice).c_str(), 0xFF000000, {1010, 500, 500, 100});
    
    drawTextAspect(std::to_string(currentMoney).c_str(), 0xFF000000, {1000, 60, 200, 100});

    if(selling) drawTextAspect("Sell menu test", 0xFF000000, {40, 790, 1160, 100});
    else drawTextAspect("Buy menu test", 0xFF000000, {40, 790, 1160, 100});
    drawTextAspect(lang->translate(std::string("item.") + inStock[selected].item->name + ".desc").c_str(), 0xFF000000, {40, 890, 1160, 100});

    update = false;
}

void Shop::updateMenu(const uint8_t *keys)
{
    int x, y;
    bool pressed = SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT);
    
    x = (int)(x / SCALE_X);
    y = (int)(y / SCALE_Y);
    if(x >= 1244 && x <= 1880)
    {
        selected = (y - 40) / 100;
        if(selected < 0 || selected >= (int) inStock.size()) selected = 0;
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
        if(selling)
        {
            currentMoney += inStock[selected].sellPrice;
            for(int i = 0; i < (int) window->level->getLocalPlayer()->playerItems.size(); i++)
            {
                if(window->level->getLocalPlayer()->playerItems[i].item->operator==(inStock[selected].item))
                {
                    if(!--window->level->getLocalPlayer()->playerItems[i].amountItems)
                    {
                        for(int j = i + 1; j < (int) window->level->getLocalPlayer()->playerItems.size(); j++)
                        {
                            window->level->getLocalPlayer()->playerItems[j - 1] = window->level->getLocalPlayer()->playerItems[j];
                        }
                    }
                    break;
                }
            }
        }
        else
        {
            currentMoney -= inStock[selected].buyPrice;
            window->level->getLocalPlayer()->addItem(inStock[selected].item);
        }
        if(!--inStock[selected].stock) inStock.erase(inStock.begin() + selected);
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
