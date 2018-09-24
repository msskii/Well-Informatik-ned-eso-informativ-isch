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
        
	public:
		RemotePlayer();
        bool connected = false;
        int direction = 0, anim = 0, walking = 0;
        int nameLen = 0;
        char *name = (char*) "MissingName";

		void onAddToLevel(Level *level) override;
		void render(int xoff, int yoff) override;
		void update(const uint8_t *keys) override;
	};
}

#endif
