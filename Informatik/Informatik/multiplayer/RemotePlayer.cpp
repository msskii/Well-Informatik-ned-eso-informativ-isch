#include "RemotePlayer.hpp"

Multiplayer::RemotePlayer::RemotePlayer()
{
    surface = IMG_Load(GET_TEXTURE_PATH("Character_Animation"));
    texture = getTexture(surface);
}


void Multiplayer::RemotePlayer::onAddToLevel(Level *level) 
{

}

void Multiplayer::RemotePlayer::render(int xoff, int yoff)
{
	SDL_Rect r = { (int) data.x_pos + xoff + PLAYER_OFFSET_X, (int) data.y_pos + yoff + PLAYER_OFFSET_Y, (int) data.width, (int) data.height };
    //fillRect(0xAFFF00FF, r);
    
    SDL_Rect src = {32 * anim, (walking * 4 + direction) * 64, 32, 64};
    renderWithShading(texture, src, r);
}

void Multiplayer::RemotePlayer::update(const uint8_t *keys) 
{

}
