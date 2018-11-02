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

class Shop : public Menu
{
private:
    int currentMoney = 0;
    std::vector<Item> inStock;
    
public:
    Shop(const char* backgroundPath, int currentMoney, std::vector<Item> inStock);
    
    bool shouldWindowClose() override;
    void renderMenu() override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* Shop_hpp */
