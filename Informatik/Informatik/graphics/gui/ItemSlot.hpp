//
//  ItemSlot.hpp
//  Informatik
//
//  Created by Aaron Hodel on 08.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef ItemSlot_hpp
#define ItemSlot_hpp

#include "../overlay/elements/Element.hpp"
#include "../../items/Item.hpp"
#include "../../config.h"

class ItemSlot : public Element
{
private:
    bool hoverOver = false;
    cachedTexture texture;
    bool needsUpdate = false;
    
public:
    InventoryElement renderItem;
    ItemSlot(InventoryElement element);
    
    void render(SDL_Renderer *renderer) override;
    void processEvent(Menu *menu, SDL_Event e) override;
};

#endif /* ItemSlot_hpp */
