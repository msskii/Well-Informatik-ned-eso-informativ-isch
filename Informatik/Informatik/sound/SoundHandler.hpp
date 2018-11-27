//
//  SoundHandler.hpp
//  Informatik
//
//  Created by Aaron Hodel on 27.11.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef SoundHandler_hpp
#define SoundHandler_hpp

#include "../util/SDL_Util.hpp"

#define AUDIO_BUFFER_SIZE 1024

extern void initSound();
extern void playSound(const char* path, int num);

#endif /* SoundHandler_hpp */
