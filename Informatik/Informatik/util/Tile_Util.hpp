//
//  Tile_Util.hpp
//  Informatik
//
//  Created by Aaron Hodel on 29.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Tile_Util_hpp
#define Tile_Util_hpp

#include "SDL_Util.hpp"

extern SDL_Surface *loadTileVariant(uint16_t tileNumber, uint8_t variant);
extern SDL_Surface *loadTile(uint16_t tileNumber, uint8_t &variant);

#endif /* Tile_Util_hpp */
