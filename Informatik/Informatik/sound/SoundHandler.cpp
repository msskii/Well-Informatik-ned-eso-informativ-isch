//
//  SoundHandler.cpp
//  Informatik
//
//  Created by Aaron Hodel on 27.11.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "SoundHandler.hpp"

Mix_Music *currentlyPlaying = nullptr;

void initSound()
{
    int res = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16SYS, 2, AUDIO_BUFFER_SIZE);
    if(res == -1)
    {
        printf("[ERROR] Could not initialize sound subsytem correctly... %s\n", Mix_GetError());
        exit(0);
    }
    
    Mix_VolumeMusic(50);
}

void playSound(const char *path, int num)
{
    if(currentlyPlaying != nullptr) Mix_FreeMusic(currentlyPlaying);
    currentlyPlaying = Mix_LoadMUS(GET_FILE_PATH(AUDIO_PATH, path));
    if(!currentlyPlaying) printf("[ERROR] Loading music: %s\n", Mix_GetError());
    Mix_PlayMusic(currentlyPlaying, num);
}
