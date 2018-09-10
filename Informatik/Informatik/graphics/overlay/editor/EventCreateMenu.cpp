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
        EventCreateMenu* m = (EventCreateMenu*) menu;
        
        m->updateArguments();
        
		EventData eventData = {};
		eventData.event_x = m->x_slider->currentValue;
		eventData.event_y = m->y_slider->currentValue;
		eventData.event_w = m->w_slider->currentValue;
		eventData.event_h = m->h_slider->currentValue;
        
		eventData.event_action = (EVENT_ACTION) m->actions->currentID;
		eventData.event_type_filter = (EVENT_TYPE) m->type_filter->currentID;
        
		eventData.triggerAmount = m->amount_slider->currentValue; // As many times triggered as you want
		eventData.event_id_dependency = m->dependency_slider->currentValue; // No Event needs to be triggered first

		int evtID = m->id_slider->currentValue;
		eventData.event_id = evtID; // Auto increment & start from one

        menu->close();
        for(size_t i = 0; i < menu->window->level->events.size(); i++)
        {
            if(menu->window->level->events[i]->event_data.event_id == evtID)
            {
                // Replace & return
                menu->window->level->events[i] = new Event(eventData, m->arguments);
                return;
            }
        }
        menu->window->level->events.push_back(new Event(eventData, m->arguments));
    }
}

static void addArgumentSliders(Menu *menu, DropDownElement element)
{
    EventCreateMenu *m = (EventCreateMenu*) menu;
    int oa = m->argumentCount;
    for(int i = 0; i < oa; i++) m->removeElement(m->argumentSliders[i]);
    
    m->argumentCount = NUM_ARGS[element.id];
    m->argumentSliders = new Slider*[m->argumentCount];
    uint8_t* a2 = (uint8_t*) malloc(m->argumentCount);
    memcpy(a2, m->arguments, oa);
    m->arguments = a2;
    
    for(int i = 0; i < m->argumentCount; i++) m->argumentSliders[i] = (Slider*) m->addElement(new Slider(0, 0xFF, m->arguments[i], 600, 100 * i, 500, 100, 7 + i));
}

EventCreateMenu::EventCreateMenu()
{
    addElement(new Text("ID", 0, 0, 100, 100));
    id_slider = (Slider*) addElement(new Slider(0, 0xFF, 100, 000, 500, 100, 0));

    addElement(new Text("X", 0, 100, 100, 100));
    addElement(new Text("Y", 0, 200, 100, 100));
    addElement(new Text("W", 0, 300, 100, 100));
    addElement(new Text("H", 0, 400, 100, 100));

    x_slider = (Slider*) addElement(new Slider(0, 0xFFF, 100, 100, 500, 100, 1));
    y_slider = (Slider*) addElement(new Slider(0, 0xFFF, 100, 200, 500, 100, 2));
    w_slider = (Slider*) addElement(new Slider(0, 0xFFF, 100, 300, 500, 100, 3));
    h_slider = (Slider*) addElement(new Slider(0, 0xFFF, 100, 400, 500, 100, 4));
    
    addElement(new Text("#", 0, 500, 100, 100));
    addElement(new Text("Dep", 0, 600, 100, 100));
    amount_slider = (Slider*) addElement(new Slider(0, 0xFF, 100, 500, 500, 100, 5));
    dependency_slider = (Slider*) addElement(new Slider(0, 0xFF, 100, 600, 500, 100, 6));

    addElement(new Button(buttonClick, "Cancel", 0, 900, 250, 100, 0));
    addElement(new Button(buttonClick, "Ok", 325, 900, 100, 100, 1));
    
    actions = new DropDown(0, 0, 700, 600, 100, 0); // Default 0
    actions->setCallback(addArgumentSliders);
    actions->toTheSide = true;
    actions->addOption(0, "No Action");
    actions->addOption(1, "Move Player");
    actions->addOption(2, "Interact with NPC");
    addElement(actions);
    addArgumentSliders(this, {0});
    
    type_filter = new DropDown(0, 0, 800, 600, 100, 0);
    type_filter->toTheSide = true;
    type_filter->addOption(0, "All Events");
    type_filter->addOption(1, "Step on");
    type_filter->addOption(2, "Game loop");
    type_filter->addOption(3, "Player interact");
    type_filter->addOption(4, "NPC finished talking");
    addElement(type_filter);
}

EventCreateMenu::EventCreateMenu(Event *evt)
{
    id_slider = (Slider*) addElement(new Slider(0, 0xFF, evt->event_data.event_id, 0, 000, 500, 100, 0));
    
    addElement(new Text("X", 0, 100, 100, 100));
    addElement(new Text("Y", 0, 200, 100, 100));
    addElement(new Text("W", 0, 300, 100, 100));
    addElement(new Text("H", 0, 400, 100, 100));
    
    x_slider = (Slider*) addElement(new Slider(0, 0xFFF, evt->event_data.event_x, 100, 100, 500, 100, 1));
    y_slider = (Slider*) addElement(new Slider(0, 0xFFF, evt->event_data.event_y, 100, 200, 500, 100, 2));
    w_slider = (Slider*) addElement(new Slider(0, 0xFFF, evt->event_data.event_w, 100, 300, 500, 100, 3));
    h_slider = (Slider*) addElement(new Slider(0, 0xFFF, evt->event_data.event_h, 100, 400, 500, 100, 4));
    
    addElement(new Text("#", 0, 500, 100, 100));
    addElement(new Text("Dep", 0, 600, 100, 100));
    amount_slider = (Slider*) addElement(new Slider(0, 0xFF, evt->event_data.triggerAmount, 100, 500, 500, 100, 5));
    dependency_slider = (Slider*) addElement(new Slider(0, 0xFF, evt->event_data.event_id_dependency, 100, 600, 500, 100, 6));

    actions = new DropDown(evt->event_data.event_action, 0, 700, 600, 100, 0);
    actions->setCallback(addArgumentSliders);
    actions->toTheSide = true;
    actions->addOption(0, "No Action");
    actions->addOption(1, "Move Player");
    actions->addOption(2, "Interact with NPC");
    addElement(actions);
    
    argumentCount = NUM_ARGS[evt->event_data.event_action];
    argumentSliders = new Slider*[argumentCount];
    arguments = evt->arguments;
    addArgumentSliders(this, {evt->event_data.event_action});
    
    type_filter = new DropDown(evt->event_data.event_type_filter, 0, 800, 600, 100, 0);
    type_filter->toTheSide = true;
    type_filter->addOption(0, "All Events");
    type_filter->addOption(1, "Step on");
    type_filter->addOption(2, "Game loop");
    type_filter->addOption(3, "Player interact");
    type_filter->addOption(4, "NPC finished talking");
    addElement(type_filter);
    
    addElement(new Button(buttonClick, "Cancel", 0, 900, 300, 100, 0));
    addElement(new Button(buttonClick, "Ok", 300, 900, 300, 100, 1));
}

void EventCreateMenu::updateArguments()
{
    for(int i = 0; i < argumentCount; i++) arguments[i] = argumentSliders[i]->currentValue;
}

void EventCreateMenu::switchSide()
{
    int toAdd = GAME_WIDTH - 600;
    toAdd *= isOnLeftSide ? 1 : -1;
    
    for(int i = 0; i < (int) elements.size(); i++) elements[i]->x += toAdd;
    isOnLeftSide = !isOnLeftSide;
}

bool EventCreateMenu::shouldWindowClose() { return false; }

void EventCreateMenu::renderMenu(SDL_Renderer *renderer)
{
    COLOR(renderer, 0xFFFF0000);
    SDL_Rect event = { x_slider->currentValue + PLAYER_OFFSET_X + window->level->xoffset, y_slider->currentValue + PLAYER_OFFSET_Y + window->level->yoffset, w_slider->currentValue, h_slider->currentValue };
    SDL_RenderFillRect(renderer, &event);
    
    COLOR(renderer, 0x55FFFFFF);
    SDL_Rect r = {isOnLeftSide ? 0 : GAME_WIDTH - 600, 0, 600, GAME_HEIGHT};
    SDL_RenderFillRect(renderer, &r);
}

void EventCreateMenu::updateMenu(const uint8_t *keys)
{
    if(keys[SDL_SCANCODE_J])
    {
        if(!jpressed)
        {
            switchSide();
        }
        jpressed = true;
    } else jpressed = false;
}

void EventCreateMenu::drawOverlay(SDL_Renderer *renderer) {}
void EventCreateMenu::onOpen() {}
void EventCreateMenu::onClose() {}
