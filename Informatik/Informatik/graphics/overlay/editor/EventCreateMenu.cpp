//
//  EventCreateMenu.cpp
//  Informatik
//
//  Created by Aaron Hodel on 24.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "EventCreateMenu.hpp"

static void buttonClick(Menu *menu, Button *button)
{
    if(button->elementID == 0)
    {
        menu->close();
    }
    else if(button->elementID == 1)
    {
		SerializedEvent eventData = {};
		eventData.event_x = atoi(((TextBox*)menu->getElement<TextBox>(1))->currentText.c_str());
		eventData.event_y = atoi(((TextBox*)menu->getElement<TextBox>(2))->currentText.c_str());
		eventData.event_w = TILE_SIZE;
		eventData.event_h = TILE_SIZE;
		eventData.event_action = MOVE_PLAYER;
		eventData.event_type_filter = STEP_ON;
		eventData.triggerAmount = 0; // As many times triggered as you want
		eventData.event_id_dependency = 0; // No Event needs to be triggered first

		int evtID = atoi(((TextBox*)menu->getElement<TextBox>(0))->currentText.c_str());
		eventData.event_id = evtID; // Auto increment & start from one

		uint8_t *args = new uint8_t[NUM_ARGS[eventData.event_action]];

		memset(args, 3, NUM_ARGS[eventData.event_action]); // Set to 0

        menu->window->level->events[evtID] = Event(eventData, args);
        menu->close();
    }
}

EventCreateMenu::EventCreateMenu()
{
    addElement(new TextBox("ID", 0, 0, 500, 100, 0)); // Nr 0
    addElement(new TextBox("X", 0, 100, 500, 100, 1)); // Nr 1
    addElement(new TextBox("Y", 0, 200, 500, 100, 2)); // Nr 2

    addElement(new Button(buttonClick, "Cancel", 0, 400, 250, 100, 0));
    addElement(new Button(buttonClick, "Ok", 325, 400, 100, 100, 1));
}

EventCreateMenu::EventCreateMenu(Event *evt)
{
	addElement(new TextBox(std::to_string(evt->toStore.event_id).c_str(), 0, 0, 500, 100, 0)); // Nr 0
	addElement(new TextBox(std::to_string(evt->toStore.event_x).c_str(), 0, 100, 500, 100, 1)); // Nr 1
	addElement(new TextBox(std::to_string(evt->toStore.event_y).c_str(), 0, 200, 500, 100, 2)); // Nr 2

	addElement(new Button(buttonClick, "Cancel", 0, 400, 250, 100, 0));
	addElement(new Button(buttonClick, "Ok", 325, 400, 100, 100, 1));
}

bool EventCreateMenu::shouldWindowClose() { return false; }

void EventCreateMenu::renderMenu(SDL_Renderer *renderer)
{
    COLOR(renderer, 0xFFFFFFFF);
    SDL_Rect r = {0, 0, 500, 500};
    SDL_RenderFillRect(renderer, &r);
}

void EventCreateMenu::updateMenu(const uint8_t *keys) {}
void EventCreateMenu::onOpen() {}
void EventCreateMenu::onClose() {}
