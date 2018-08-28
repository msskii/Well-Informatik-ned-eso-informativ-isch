//
//  config.h
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef config_h
#define config_h

#define GAME_TITLE "..."

// #define FULLSCREEN_ENABLED // Comment this line if no fullscreen
// #define HIGH_RESOLUTION // Comment this line if no high resolution

#define GAME_WIDTH 1920
#define GAME_HEIGHT 1080

#define DEBUG_OVERLAY

// 16 to 9 ratio?
#ifdef HIGH_RESOLUTION
#  define WINDOW_WIDTH GAME_WIDTH
#  define WINDOW_HEIGHT GAME_HEIGHT
#else
#  define WINDOW_WIDTH 960
#  define WINDOW_HEIGHT 540
#endif

#define SPEED 10
#define SPEED 7
#define STEP_ACCURACY 100.0f

#endif /* config_h */
