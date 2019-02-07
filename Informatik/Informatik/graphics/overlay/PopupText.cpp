//
//  PopupText.cpp
//  Informatik
//
//  Created by Aaron Hodel on 04.12.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "PopupText.hpp"

PopupText::PopupText(const char *t, int delay) : text(t), decayTimer(delay), maxDecay(delay)
{
    shouldLevelBeUpdated = true;
    surface = drawTextAspect(text,0xFFFFFFFF, {GAME_WIDTH / 2 - 300, GAME_HEIGHT / 2 - 100, 600, 200}, texture, true);
    dst = {GAME_WIDTH / 2 - 300, GAME_HEIGHT / 2 - 100, (int) ((float) texture.width * texture.scale), (int) ((float) texture.height * texture.scale)};
    
}

void PopupText::renderMenu()
{
    if(decayTimer <= 0) return; // No rendering here --> else zero-division
    int d = (int)(((float) decayTimer / (float) maxDecay) * 255.0f);
    adjustAlpha(surface, d);
    gltexture = getTexture(surface);
    renderWithoutShading(gltexture, {0,0,0,0}, dst);
    --decayTimer;
}
