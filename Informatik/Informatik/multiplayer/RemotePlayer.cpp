#include "RemotePlayer.hpp"
#include "../level/Level.hpp"

Multiplayer::RemotePlayer::RemotePlayer()
{
    // We cant load textures since we're not on the main thread...
    data.collisionEnabled = false;
}


void Multiplayer::RemotePlayer::onAddToLevel(Level *level) 
{
    this->level = level;
}

void Multiplayer::RemotePlayer::render(int xoff, int yoff)
{
	SDL_Rect r = { (int) data.x_pos + xoff + PLAYER_OFFSET_X, (int) data.y_pos + yoff + PLAYER_OFFSET_Y, (int) data.width, (int) data.height * 2 };
    // printf("Rendering remote player @ %f, %f\n", data.x_pos, data.y_pos);
    SDL_Rect src = {32 * anim, (walking * 4 + direction) * 64, 32, 64};
    if(level != nullptr) renderWithShading(level->player->texture, src, r);
}

void Multiplayer::RemotePlayer::update(const uint8_t *keys) 
{

}
