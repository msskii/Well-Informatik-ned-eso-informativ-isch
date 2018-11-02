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
}

bool Shop::shouldWindowClose() { return false; }
void Shop::renderMenu() {}
void Shop::updateMenu(const uint8_t *keys) {}
void Shop::onOpen() {}
void Shop::onClose() {}
