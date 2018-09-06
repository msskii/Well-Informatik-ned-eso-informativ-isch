CXX = g++
CFLAGS = -I. -I../SDL2/include/ -I../SDL2_net/ -I../SDL2_mixer/ -I../SDL2_image/ -I../SDL2_ttf/
LIBS = -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_net -lSDL2_image -lSDL2_mixer
LDDFLAGS = -L/usr/local/lib
DEPS = 	Informatik/main.cpp \
	Informatik/enemy/Enemy.cpp \
	Informatik/enemy/Slime.cpp \
	Informatik/entity/Entity.cpp \
	Informatik/entity/NPC.cpp \
	Informatik/entity/Player.cpp \
	Informatik/entity/loader/NPCLoader.cpp \
	Informatik/graphics/Window.cpp \
	Informatik/graphics/overlay/Menu.cpp \
	Informatik/graphics/overlay/MainMenu.cpp \
	Informatik/graphics/overlay/DebugOverlay.cpp \
	Informatik/graphics/overlay/DialogOverlay.cpp \
	Informatik/graphics/overlay/PauseMenu.cpp \
	Informatik/graphics/overlay/editor/EditorOverlay.cpp \
	Informatik/graphics/overlay/editor/EventCreateMenu.cpp \
	Informatik/graphics/overlay/editor/TileEditor.cpp \
	Informatik/graphics/overlay/elements/Button.cpp \
	Informatik/graphics/overlay/elements/Dropdown.cpp \
	Informatik/graphics/overlay/elements/Element.cpp \
	Informatik/graphics/overlay/elements/Slider.cpp \
	Informatik/graphics/overlay/elements/Text.cpp \
	Informatik/graphics/overlay/elements/TextBox.cpp \
	Informatik/items/EntityItem.cpp \
	Informatik/items/Item.cpp \
	Informatik/level/Event.cpp \
	Informatik/level/Level.cpp \
	Informatik/level/Tile.cpp \
	Informatik/level/loader/LevelLoader.cpp \
	Informatik/level/loader/EventActions.cpp \
	Informatik/level/loader/EventLoader.cpp \
	Informatik/level/loader/TextLoader.cpp \
	Informatik/multiplayer/Client.cpp \
	Informatik/multiplayer/RemotePlayer.cpp \
	Informatik/multiplayer/Server.cpp \
	Informatik/multiplayer/ServerSelector.cpp \
	Informatik/projectile/Projectile.cpp \
	Informatik/tests/Tests.cpp \
	Informatik/util/FileReader.cpp \
	Informatik/util/Math_Util.cpp \
	Informatik/util/SDL_Util.cpp \
	Informatik/util/Tile_Util.cpp

prog: $(DEPS)
	$(CXX) -o ../Game $(CFLAGS) $(LDDFLAGS) $(LIBS) $(DEPS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c -o $@ $<


