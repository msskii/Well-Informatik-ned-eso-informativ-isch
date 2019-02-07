//
//  PlayerOverlay.hpp
//  Informatik
//
//  Created by Aaron Hodel on 11.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef PlayerOverlay_hpp
#define PlayerOverlay_hpp

#include "../overlay/Menu.hpp"

class PlayerOverlay : public Menu
{
private:
    SDL_Surface *backsurface, *hpbarsurface, *hpbartransparentsurface, *manabarsurface, *spelliconsurface, *spellbordersurface;
    gl_texture backtexture, hpbartexture, hpbartransparenttexture, manabartexture, spellicontexture, spellbordertexture;
    cachedTexture cachedHealth, cachedMana, cachedfloor;
    float lastHealth = 0.0f, lastMana = 0.0f;
    int lastState = 0;
    int lastfloor = 0;
    bool transition = true;
    bool kp = false, jp = false;

public:
    PlayerOverlay(Player *p);
    Player *player;
    
    bool shouldWindowClose() override;
    void renderMenu() override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* PlayerOverlay_hpp */
