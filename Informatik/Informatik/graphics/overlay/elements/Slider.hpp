//
//  Slider.hpp
//  Informatik
//
//  Created by Aaron Hodel on 28.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Slider_hpp
#define Slider_hpp

#include "Element.hpp"

typedef void (*sliderCallback)(Menu *menuIn, int newValue);

class Slider : public Element
{
protected:
    int minValue, maxValue;
    sliderCallback clbck = nullptr;
        
public:
    int currentValue = 0;

	inline void setMin(int m) { minValue = m; }
	inline void setMax(int m) { maxValue = m; }

	Slider(int min, int max, int x, int y, int w, int h, int id);
    Slider(int min, int max, int current, int x, int y, int w, int h, int id);

    inline void setCallback(sliderCallback c) { clbck = c; }
    
    void render() override;
    void processEvent(Menu *menu, SDL_Event e) override;
};

#endif /* Slider_hpp */
