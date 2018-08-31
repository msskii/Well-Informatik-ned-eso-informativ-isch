//
//  ServerSelector.hpp
//  Informatik
//
//  Created by Aaron Hodel on 22.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef ServerSelector_hpp
#define ServerSelector_hpp

#include "../graphics/overlay/Menu.hpp"

namespace Multiplayer
{
	class ServerSelector : public Menu
	{
		Menu *mainMenu;
		TextBox *tb = nullptr;

	public:
		ServerSelector(Menu *mainMenu);

		bool shouldWindowClose() override;
		void renderMenu(SDL_Renderer *renderer) override;
		void updateMenu(const uint8_t *keys) override;
		void onOpen() override;
		void onClose() override;
	};
}

#endif