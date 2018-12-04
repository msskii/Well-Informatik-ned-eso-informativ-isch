//
//  Shop.hpp
//  Informatik
//
//  Created by Aaron Hodel on 02.11.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Shop_hpp
#define Shop_hpp

#include "../overlay/Menu.hpp"
#include <vector>

typedef struct shopItem
{
    Item *item;
    int stock = 0;
    
    int buyPrice = 0;
    int sellPrice = 0;
} shopItem;

class Shop : public Menu
{
private:
    int currentMoney = 0;
    std::vector<shopItem> inStock;
    std::vector<cachedTexture> stockNameTextures;
    std::vector<cachedTexture> selectedInfo;
    int selected = 0, cooldown = 0;
    bool update = false, lastPressed = false;
    
public:
    Shop(const char* backgroundPath, int currentMoney, std::vector<shopItem> inStock);
    
    bool shouldWindowClose() override;
    void renderMenu() override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* Shop_hpp */
