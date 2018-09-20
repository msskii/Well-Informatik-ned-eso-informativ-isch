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

namespace Multiplayer
{
	class RemotePlayer : public Entity
	{
	private:

	public:
		RemotePlayer();

		void onAddToLevel(Level *level);
		void render(int xoff, int yoff);
		void update(const uint8_t *keys);
	};
}

#endif
