#include "RemotePlayer.hpp"

Multiplayer::RemotePlayer::RemotePlayer()
{

}


void Multiplayer::RemotePlayer::onAddToLevel(Level *level) 
{

}

void Multiplayer::RemotePlayer::render(int xoff, int yoff)
{
	SDL_Rect r = { (int) data.x_pos + xoff + PLAYER_OFFSET_X, (int) data.y_pos + yoff + PLAYER_OFFSET_Y, (int) data.width, (int) data.height };
	//COLOR(renderer, 0xAFFF00FF); // Pink with some alpha
	//SDL_RenderFillRect(renderer, &r);
    fillRect(0xAFFF00FF, r);
}

void Multiplayer::RemotePlayer::update(const uint8_t *keys) 
{

}
