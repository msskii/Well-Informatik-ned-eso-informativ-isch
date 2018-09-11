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
    SDL_Texture *backtexture = nullptr, *hpbartexture = nullptr, *hpbartransparenttexture = nullptr;
    cachedTexture cachedHealth;
    float lastHealth = 0.0f;
    int lastState = 0;
    bool transition = true;

public:
    PlayerOverlay(Player *p);
    Player *player;
    
    bool shouldWindowClose() override;
    void renderMenu(SDL_Renderer *renderer) override;
    void drawOverlay(SDL_Renderer *renderer) override;
    void updateMenu(const uint8_t *keys) override;
    void onOpen() override;
    void onClose() override;
};

#endif /* PlayerOverlay_hpp */