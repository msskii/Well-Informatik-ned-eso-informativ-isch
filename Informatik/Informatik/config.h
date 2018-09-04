//
//  config.h
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef config_h
#define config_h

// All enable / disable options are just commented = disabled & uncommented = enabled

// ======================
// Debug stuff
// ======================

// #define DEBUG_OVERLAY
#define DEBUG_RANDOM // Always same random values in the same order if enabled
// #define ENABLE_TEST_MULTIPLAYER // Enable the option to join a server in the main menu


// ======================
// Window & Game stuff stuff
// ======================

#define GAME_TITLE "..."
// #define FULLSCREEN_ENABLED // Comment this line if no fullscreen
// #define HIGH_RESOLUTION // Comment this line if no high resolution

#define GAME_WIDTH 1920
#define GAME_HEIGHT 1080

#ifdef HIGH_RESOLUTION
#  define WINDOW_WIDTH GAME_WIDTH
#  define WINDOW_HEIGHT GAME_HEIGHT
#else
#  define WINDOW_WIDTH 960
#  define WINDOW_HEIGHT 540
#endif


// ======================
// Tile stuff
// ======================
#define TILE_SIZE 64

// ======================
// Projectile stuff
// ======================

#define PROJECTILE_SPEED 7

// ======================
// Player stuff
// ======================

#define SPEED 7
#define STEP_ACCURACY 100.0f

// Same as tile size
#define PLAYER_WIDTH 64
#define PLAYER_HEIGHT 64
#define PLAYER_OFFSET_X ((GAME_WIDTH + PLAYER_WIDTH) / 2)
#define PLAYER_OFFSET_Y ((GAME_HEIGHT + PLAYER_HEIGHT) / 2)

#endif /* config_h */
