//
//  RemotePlayer.hpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright � 2018 Aaron Hodel. All rights reserved.
//

#ifndef RemotePlayer_hpp
#define RemotePlayer_hpp

#include "../entity/Entity.hpp"
#include "Buffer.hpp"

namespace Multiplayer
{
	class RemotePlayer : public Entity
	{
	private:
        SDL_Surface *surface;
        gl_texture texture;
        
	public:
		RemotePlayer();
        bool connected = false;
        int direction = 0, anim = 0, walking = 0;

		void onAddToLevel(Level *level);
		void render(int xoff, int yoff);
		void update(const uint8_t *keys);
	};
}

#endif
