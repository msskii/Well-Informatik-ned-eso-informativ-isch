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
#include "../graphics/overlay/light/LightSource.hpp"
enum ProjectileType{
    PROJECTILE_ARROW,
    PROJECTILE_FIREBALL
};
class Projectile : public Entity
{
protected:
    SDL_Surface *surface;
    gl_texture texture;
    SDL_Rect hitbox = {0,0,0,0};
    
    int max_anim = 1;
    int current_anim = 0, anim_timer = 0;
    
    int param = 0;
    int projectileSpeed = PROJECTILE_SPEED;
    
    
    vector2d velocity = {0, 0};
    int despawnTimer, ticksPassed = 0; // The maximum amount of frames a projectile can live --> max distance is |velocity| * timer
    
    Entity *sender = nullptr; // Nullptr if from player, entity otherwise (enemy probably)
    lightSource light;
    
public:
    float rotationAngle = 0; // Rotation of this projectile
    float damage = 10.0f;
    ProjectileType projectileType;
    
    Projectile(float x, float y, float ra, ProjectileType pt);
    Projectile(float x, float y, float ra, ProjectileType pt, int param);
    
    void onAddToLevel(Level *level) override;
    void render(int xoff, int yoff) override;
    void update(const uint8_t *keys) override;
    void setup(float x, float y);
};

#endif /* Projectile_hpp */
