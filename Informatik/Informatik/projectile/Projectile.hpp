//
//  Projectile.hpp
//  Informatik
//
//  Created by Aaron Hodel on 04.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#ifndef Projectile_hpp
#define Projectile_hpp

#include "../entity/Entity.hpp"

class Projectile : public Entity
{
private:
    SDL_Surface *surface;
    SDL_Texture *texture = nullptr;
    
    vector2d velocity = {0, 0};
    int despawnTimer = 600; // The maximum amount of frames a projectile can live
    
public:
    float rotationAngle = 0; // Rotation of this projectile
    
    Projectile(float x, float y, float ra);
    
    void onAddToLevel(Level *level) override;
    void render(SDL_Renderer *renderer, int xoff, int yoff) override;
    void update(const uint8_t *keys) override;
};

#endif /* Projectile_hpp */
