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
    SDL_Surface *backsurface, *backsurface_under, *hpbarsurface, *hpbartransparentsurface, *manabarsurface, *spelliconsurface, *spellbordersurface;
    gl_texture backtexture,backtexture_under, hpbartexture, hpbartransparenttexture, manabartexture, spellicontexture, spellbordertexture;
    int lastState = 0;
    int lastfloor = 0;
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
