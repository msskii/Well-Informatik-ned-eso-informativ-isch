//
//  Projectile.cpp
//  Informatik
//
//  Created by Aaron Hodel on 04.09.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Projectile.hpp"
#include "../level/Level.hpp"
#define wavespeed 2*PI/40

Projectile::Projectile(float x, float y, float ra, ProjectileType pt) : rotationAngle(ra), projectileType(pt)
{
    setup(x, y);
    
}

Projectile::Projectile(float x, float y, float ra, ProjectileType pt, int param) : rotationAngle(ra), projectileType(pt), param(param)
{
    setup(x, y);
}

void Projectile::setup(float x, float y){
    data.x_pos = x;
    data.y_pos = y;
    
    switch (projectileType) {
        case PROJECTILE_FIREBALL:
            projectileSpeed *= 0.8;
            data.width = 64;
            data.height = 64;
            despawnTimer = 60;
            if (param == 1) light = createLightSource(0, 0, 10.0f, 1.0f, 0xFF0000FF, 0.4f, 1.0f);
            else light = createLightSource(0, 0, 10.0f, 1.0f, 0xFFFF0000, 0.4f, 1.0f);
            break;
            
        case PROJECTILE_ARROW:
            data.width = 64;
            data.height = 64;
            surface = IMG_Load(GET_TEXTURE_PATH("projectiles/arrow_ur"));
            // createSource: x, y, brightness, radius, color, glowRatio, colorPart
            light = createLightSource(0, 0, 10.0f, 1.0f, 0xFFF00000, 0.4f, 0.4f);
            despawnTimer = 60 * 10;
            break;
            
        default:
            break;
    }
    velocity.x = cos(rotationAngle) * projectileSpeed;
    velocity.y = -sin(rotationAngle) * projectileSpeed;
    
}

void Projectile::onAddToLevel(Level *level) {}

void Projectile::render(int xoff, int yoff)
{
    SDL_Rect r = getBoundingBox();
    TRANSFORM_LEVEL_POS(r, xoff, yoff);
    
    switch (projectileType) {
        case PROJECTILE_FIREBALL:
            if (param == 1) {
                fillRect(0xFFFF00FF, r);
            }else fillRect(0xFFFFFF00, r);
            moveLightSource(light, (float) (r.x + data.width / 2.0f), (float) (r.y + data.height / 2.0f));
            level->window->lights.injectLight(light);
            break;
            
        default:
            if(texture.id == 0) texture = getTexture(surface);
            SDL_Rect src = {current_anim * 32, 0, 32, 32};
            
            if(max_anim != 1) renderWithShading(texture, src, r); // Animations cant be rotated...
            else renderWithRotation(texture, src, r, -rotationAngle + (float) PI / 4.0f, true);
            
            // level->window->lights.addLight((float) (r.x + data.width / 2.0f), (float) (r.y + data.height / 2.0f), 10.0f, 0xFFF00000, 1.0f, 0.2f);
            moveLightSource(light, (float) (r.x + data.width / 2.0f), (float) (r.y + data.height / 2.0f));
            level->window->lights.injectLight(light);
            break;
    }
    
}

void Projectile::update(const uint8_t *keys)
{
    data.x_pos += velocity.x;
    data.y_pos += velocity.y;
    switch (projectileType) {
        case PROJECTILE_FIREBALL:
            if (velocity.len() != 0) {
                data.x_pos += 10 * cos(rotationAngle - PI / 2) * cos(wavespeed * ticksPassed) * param;
                data.y_pos += 10 * sin(rotationAngle - PI / 2) * cos(wavespeed * ticksPassed) * param;
            }
            break;
            
        default:
            break;
    }
    
    SDL_Rect r = getBoundingBox();
    Player *player = level->getLocalPlayer();
    TRANSFORM_LEVEL_POS(r, player->getOffsetX(), player->getOffsetY());
    
    if(++anim_timer >= 7)
    {
        current_anim = (current_anim + 1) % max_anim;
        anim_timer = 0;
    }
    
    if(level->remoteLevel) // If we're on the server, the projectile shouldnt despawn because it is out of sight
    {
        if(++ticksPassed > despawnTimer)
        {
            // Despawn...
            level->removeEntity(this); // Stops render & update
        }
    }
    else
    {
        if(r.x < 0 || r.x + r.w >= GAME_WIDTH || r.y < 0 || r.y + r.h >= GAME_HEIGHT || ++ticksPassed > despawnTimer)
        {
            // Despawn...
            level->removeEntity(this); // Stops render & update
        }
    }
    if (hitbox.h == 0 || hitbox.w == 0) {
        float x_pos_front = data.x_pos + data.width * (0.5f + cos(rotationAngle) / 2.0f);
        float y_pos_front = data.y_pos + data.height * (0.5f + sin(rotationAngle) / 2.0f);
        
        float x_pos_end = data.x_pos + data.width * (0.5f - cos(rotationAngle) / 2.0f);
        float y_pos_end = data.y_pos + data.height * (0.5f - sin(rotationAngle) / 2.0f);
        
        float xstep = (x_pos_end - x_pos_front) / PROJECTILE_ACCURACY;
        float ystep = (y_pos_end - y_pos_front) / PROJECTILE_ACCURACY;
        // Find buildings
        for(int i = 0; i <= PROJECTILE_ACCURACY; i++)
        {
            Tile tile = level->getTile((int)((x_pos_front + i * xstep) / TILE_SIZE), (int)((y_pos_front + i * ystep) / TILE_SIZE));
            if(level->getBuildingCollision(x_pos_front + i * xstep, y_pos_front + i * ystep) || tile.data.tileZ > data.height || tile.Tile_surface == nullptr)
            {
                velocity = {0, 0}; // Stop right at the wall
                
            }
        }
        
        // Find enemies in close proximity?
        for(size_t i = 0; i < level->entities.size(); i++)
        {
            auto *enemy = dynamic_cast<Enemy*>(level->entities[i]);
            if(enemy == nullptr || !enemy->isAlive) continue; // Couldnt cast to enemy --> isnt an enemy
            
            if(LENGTH(enemy->data.x_pos - data.x_pos, enemy->data.y_pos - data.y_pos) >  LENGTH(max(data.width, enemy->data.width), max(data.height, enemy->data.height)))
            {
                // Out of reach... continue
                continue;
            }
            
            for(int i = 0; i <= PROJECTILE_ACCURACY; i++)
            {
                if(enemy->isInsideEntity(x_pos_front + i * xstep, y_pos_front + i * ystep))
                {
                    enemy->takeDamage(damage);
                    level->removeEntity(this);
                    return; // Only damage the first entity we encounter, not more
                }
            }
        }
    }else{
        int xstep;
        int ystep;
        for(int i = 0; i <= int(data.width / TILE_SIZE) + 1; i++){
            for(int j = 0; j <= int(data.height / TILE_SIZE) + 1; j++){
                (TILE_SIZE * i > data.width) ? xstep = data.width : xstep = i * TILE_SIZE;
                (TILE_SIZE * j > data.height) ? ystep = data.height : ystep = j * TILE_SIZE;
                Tile tile = level->getTile((int)((data.x_pos + xstep) / TILE_SIZE), (int)((data.y_pos + ystep) / TILE_SIZE));
                if(level->getBuildingCollision(data.x_pos + xstep, data.y_pos + ystep) || tile.data.tileZ > data.height || tile.Tile_surface == nullptr)
                {
                    velocity = {0, 0}; // Stop right at the wall
                }
            }
        }
        
        
    }
}
