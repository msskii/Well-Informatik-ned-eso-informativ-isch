//
//  Player.hpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#ifdef __APPLE__
#  include <SDL2/SDL.h> // Other path than on windows
#else
#  include <SDL2.h>
#endif

class Player
{
private:
    float _x = 0, _y = 0;
    
public:
    void updateMovement(float dx, float dy);
    Player();
    
    void render(SDL_Renderer *renderer);
    
};

#endif /* Player_hpp */
