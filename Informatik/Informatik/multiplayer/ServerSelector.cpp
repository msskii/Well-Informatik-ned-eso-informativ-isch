#include "ServerSelector.hpp"

Multiplayer::ServerSelector::ServerSelector(Menu *mainMenu)
{
	this->mainMenu = mainMenu;

	tb = (TextBox*) addElement(new TextBox("IP addr", 0, 0, 500, 100, 0));
    name = (TextBox*) addElement(new TextBox("Username", 0, 100, 500, 100, 0));
}

bool Multiplayer::ServerSelector::shouldWindowClose() { return false; }

void Multiplayer::ServerSelector::renderMenu()
{
	SDL_Rect r = {0, 0, 500, 100};
    fillRect(0xFFFFFFFF, r);
}

void Multiplayer::ServerSelector::updateMenu(const uint8_t *keys) 
{
	if (keys[SDL_SCANCODE_RETURN])
	{
#ifdef ENABLE_TEST_MULTIPLAYER
		if(!window->level->connectToServer(tb->currentText.c_str(), name->currentText)) return; // Dont close yet
#endif
		close();
		this->mainMenu->close();
	}
}

void Multiplayer::ServerSelector::onOpen() {}
void Multiplayer::ServerSelector::onClose() {}
