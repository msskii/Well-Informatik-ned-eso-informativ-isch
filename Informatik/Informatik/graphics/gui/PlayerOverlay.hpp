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
    SDL_Surface *backsurface, *hpbarsurface, *hpbartransparentsurface;
    gl_texture backtexture, hpbartexture, hpbartransparenttexture;
    cachedTexture cachedHealth;
    float lastHealth = 0.0f;
    int lastState = 0;
    bool transition = true;

public:
    PlayerOverlay(Player *p);
    Player *player;
    
    bool shouldWindowClose() override;
    void renderMenu() override;
    void drawOverlay() override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* PlayerOverlay_hpp */
