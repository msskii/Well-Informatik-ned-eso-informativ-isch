//
//  Player.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Player.hpp"
#define MAX_STEP 1

Player::Player(Level *l) : level(l)
{
    player_surface = IMG_Load(GET_TEXTURE_PATH("Character_Animation"));
    texture = getTexture(player_surface);
    
    for(int i = 0; i < INV_WIDTH * INV_HEIGHT; i++)
    {
        playerItems[i] = {nullptr, i, 0};
    }
}

// Helper function for intersections with other things (xpos & ypos are the players position while the rest are the parameters of the thing trying to compare to)
bool intersectWith(int xpos1, int ypos1, int x, int y, int w, int h)
{
    if((xpos1) >= x && (xpos1) <= x + w && (ypos1) >= y && (ypos1) <= y + h) return true;
    if((xpos1 + PLAYER_WIDTH) > x && (xpos1 + PLAYER_WIDTH) < x + w && (ypos1) > y && (ypos1) <= y + h) return true;
    if((xpos1) >= x && (xpos1) <= x + w && (ypos1 + PLAYER_HEIGHT) > y && (ypos1 + PLAYER_HEIGHT) < y + h) return true;
    if((xpos1 + PLAYER_WIDTH) > x && (xpos1 + PLAYER_WIDTH) < x + w && (ypos1 + PLAYER_HEIGHT) > y && (ypos1 + PLAYER_HEIGHT) < y + h) return true;
    return false;
}

#define MARGIN 4

bool Player::isInside(float dx, float dy)
{
    if(x_pos + dx < 0 || x_pos + dx >= TILE_SIZE * level->width || y_pos + dy < 0 || y_pos + dy >= TILE_SIZE * level->height) return true; // Out of bounds = you cant walk

    for(int point_index = 0; point_index < 4; point_index++)
    {
        float player_x_offset = dx + MARGIN + (PLAYER_WIDTH - 2 * MARGIN) * (point_index % 2);
        float player_y_offset = dy + MARGIN + (PLAYER_HEIGHT - 2 * MARGIN) * (int)(point_index / 2);
        
        if(level->getTile((int)((x_pos + player_x_offset) / TILE_SIZE), (int)((y_pos + player_y_offset) / TILE_SIZE)).data.tileZ != _z) return true;
        if(level->getBuildingCollision(x_pos + player_x_offset, y_pos + player_y_offset)) return true;

        // Test point at index point_index
        for(size_t i = 0; i < level->entities.size(); i++)
        {
            auto *entity = level->entities[i];
            
            auto *enemy = dynamic_cast<Enemy*>(entity);
            auto *projectile = dynamic_cast<Projectile*>(entity);
            auto *item = dynamic_cast<EntityItem*>(entity);
            
            if(enemy != nullptr && enemy->isAlive)
            {
                // TODO
                if(enemy->isInside(x_pos + player_x_offset, y_pos + player_y_offset))
                {
                    takeDamage(enemy->onDamaging());
                    
                }
            }
            else if(projectile != nullptr)
            {
                // Currently no collision with a projectile
            }
            else if(item != nullptr)
            {
                if(x_pos + player_x_offset >= item->data.x_pos && x_pos + player_x_offset <= item->data.x_pos + item->data.width && y_pos + player_y_offset >= item->data.y_pos && y_pos + player_y_offset <= item->data.y_pos + item->data.height)
                {
                    item->pickUp(); // Send the item the message we picked it up
                    level->removeEntity(item);
                }
            }
            else if(intersectWith((int)(x_pos + player_x_offset), (int)(y_pos + player_y_offset), (int) entity->data.x_pos, (int) entity->data.y_pos, (int) entity->data.width, (int) entity->data.height)) return true;
        }
    }
    
    return false;
}

void Player::takeDamage(float amount)
{
    if(graceLeft <= 0)
    {
        graceLeft = (int)(gracePeriode * 60); // Wait gracePeriod seconds
        currentHealth -= amount;
        if(currentHealth <= 0)
        {
            isAlive = false;
        }
    }
}

void Player::correctMovement(float &dx, float &dy)
{
    if(isInside(dx, dy))
    {        
        float xmax = STEP_ACCURACY, ymax = STEP_ACCURACY;
        
        if(dx != 0) for(xmax = 1; xmax <= STEP_ACCURACY; xmax++) if(isInside(dx * xmax / STEP_ACCURACY, dy)) break;
        --xmax; // Not up to and with (inside), just up to the thing
        
        if(dy != 0) for(ymax = 1; ymax <= STEP_ACCURACY; ymax++) if(isInside(dx * xmax / STEP_ACCURACY, dy * ymax / STEP_ACCURACY)) break;
        --ymax; // Not up to and with (inside), just up to the thing
        
        // Check x again
        if(dx != 0) for(xmax = 1; xmax <= STEP_ACCURACY; xmax++) if(isInside(dx * xmax / STEP_ACCURACY, dy * ymax / STEP_ACCURACY)) break;
        --xmax;
        
        if(xmax < 0) xmax = 0;
        if(ymax < 0) ymax = 0;

        dx *= xmax / STEP_ACCURACY;
        dy *= ymax / STEP_ACCURACY;
    }
}

void Player::updateMovement(float dx, float dy)
{
    if(!inControl) return;

    // Walking into stuff
    if(dx > 0) direction = RIGHT;
    else if(dx < 0) direction = LEFT;
    else if(dy > 0) direction = DOWN;
    else if(dy < 0) direction = UP;
    
    walking = dx != 0 || dy != 0;
    if(walking) correctMovement(dx, dy);
    
    if(dx > 0) direction = RIGHT;
    else if(dx < 0) direction = LEFT;
    else if(dy > 0) direction = DOWN;
    else if(dy < 0) direction = UP;
    
    float movement_amount = LENGTH(dx, dy); // Length of vector
    if(movement_amount >= SPEED)
    {
        dx /= movement_amount / (float) SPEED;
        dy /= movement_amount / (float) SPEED;
    }
    
    x_pos += dx;
    y_pos += dy;
    
    if(x_pos < 0) x_pos = 0;
    if(y_pos < 0) y_pos = 0;
    if(x_pos >= (level->width - 1) * TILE_SIZE) x_pos = (float)((level->width - 1) * TILE_SIZE);
    if(y_pos >= (level->height - 1) * TILE_SIZE) y_pos = (float)((level->height - 1) * TILE_SIZE);
    
    _x = x_pos;
    _y = y_pos;
    
    if(_x <= ((GAME_WIDTH + PLAYER_WIDTH) / 2))
    {
        _x = ((GAME_WIDTH + PLAYER_WIDTH) / 2);
        xoff = (int)(((GAME_WIDTH + PLAYER_WIDTH) / 2) - x_pos);
    }
    else if(_x >= level->width * TILE_SIZE - ((GAME_WIDTH - PLAYER_WIDTH) / 2))
    {
        _x = (float) level->width * TILE_SIZE - ((GAME_WIDTH - PLAYER_WIDTH) / 2.0f);
        xoff = (int)(level->width * TILE_SIZE - ((GAME_WIDTH - PLAYER_WIDTH) / 2) - x_pos);
    }
    
    if(_y < ((GAME_HEIGHT + PLAYER_HEIGHT) / 2))
    {
        _y = ((GAME_HEIGHT + PLAYER_HEIGHT) / 2);
        yoff = (int)(((GAME_HEIGHT + PLAYER_HEIGHT) / 2) - y_pos);
    }
    else if(_y >= level->height * TILE_SIZE - ((GAME_HEIGHT - PLAYER_HEIGHT) / 2))
    {
        _y = (float) level->height * TILE_SIZE - ((GAME_HEIGHT - PLAYER_HEIGHT) / 2.0f);
        yoff = (int)(level->height * TILE_SIZE - ((GAME_HEIGHT - PLAYER_HEIGHT) / 2) - y_pos);
    }
}

void Player::render(int x, int y)
{
    if(graceLeft > 0) graceLeft = graceLeft - 1;

    //animation speed scales with player speed
    if(walking && (timer++ * SPEED) >= 50)
    {
        animSet = 1;
        timer = 0;
        anim = (anim + 1) % 4;
    }
    else if(!walking && timer++ >= 10)
    {
        animSet = 0;
        timer = 0;
        anim = (anim + 1) % 4;
    }

    SDL_Rect src = {32 * anim, (animSet * 4 + direction) * 64, 32, 64};
    SDL_Rect dst = {PLAYER_OFFSET_X - xoff, PLAYER_OFFSET_Y - yoff, PLAYER_WIDTH, 128};
    renderWithShading(texture, src, dst);
    renderStats(xoff, yoff);
}

void Player::renderStats(int xoff, int yoff)
{
    if(animationHealth <= 0 || currentHealth == maxHealth) return; // Dead or full health
    
    if(animationHealth != currentHealth)
    {
        float difference = currentHealth - animationHealth;
        float step = difference / 60.0f;
        if(abs(step) <= 0.05f) step = difference;
        else while(abs(step) <= 0.5f) step *= 2; // Just finish it
        animationHealth += step;
    }
    
    SDL_Rect hpbar = { (int) PLAYER_OFFSET_X - xoff, (int) PLAYER_OFFSET_Y - yoff - 40, (int) TILE_SIZE, 20 };
    
    //COLOR(renderer, 0xFF000000);
    //SDL_RenderFillRect(renderer, &hpbar); // Draw black border
    
    fillRect(0xFF000000, hpbar);
    
    // If it ever does not work: add ceil() around those four lines
    hpbar.x += (int)ceil(1.0 / SCALE_X);
    hpbar.y += (int)ceil(1.0 / SCALE_Y);
    hpbar.w -= (int)ceil(2.0 / SCALE_X);
    hpbar.h -= (int)ceil(2.0 / SCALE_Y);
    
    //COLOR(renderer, 0xFFFF0000); // Color red for depleted hp
    //SDL_RenderFillRect(renderer, &hpbar); // Full background
    fillRect(0xFFFF0000, hpbar);
    
    hpbar.w = (int)(TILE_SIZE * animationHealth / maxHealth);
    //COLOR(renderer, 0xFF00FF00);
    //SDL_RenderFillRect(renderer, &hpbar); // Draw hp in green
    fillRect(0xFF00FF00, hpbar);
    // Draw box around hp bar
    
}
