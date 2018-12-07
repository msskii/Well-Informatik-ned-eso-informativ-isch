//
//  ItemList.h
//  Informatik
//
//  Created by Aaron Hodel on 07.12.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef ItemList_h
#define ItemList_h

#include "Item.hpp"
#include "EntityItem.hpp"
#include "../config/ConfigLoader.hpp"

class ItemData : public ConfigLoader
{
private:
    
public:
    ItemData(const char *path) : ConfigLoader(path, false) {}
    
    inline int getItemBuyValue(const char* item) { return getInt((std::string("item.") + item + ".value.buy").c_str()); }
    inline int getItemSellValue(const char* item) { int a = getInt((std::string("item.") + item + ".value.sell").c_str()); return a == 0 ? getItemBuyValue(item) * 9 / 10 : a; }
    inline int getItemStat(const char* item) { return getInt((std::string("item.") + item + ".stat").c_str()); }
};

extern ItemData *itemData;

#endif /* ItemList_h */
