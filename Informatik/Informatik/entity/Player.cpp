//
//  Player.cpp
//  Informatik
//
//  Created by Aaron Hodel on 20.08.18.
//  Copyright © 2018 Aaron Hodel. All rights reserved.
//

#include "Player.hpp"
#include "../level/Level.hpp"
#include "../projectile/Spell.hpp"
#define MAX_STEP 1

Player::Player(Level *l) : current_level(l)
{
    //load Playertexture
    player_surface = IMG_Load(GET_TEXTURE_PATH("player/Character_Animation"));
    
    hurt_surface = SDL_CreateRGBSurfaceWithFormat(0, player_surface->w, player_surface->h, 32, SDL_PIXELFORMAT_ARGB8888);
    SDL_BlitSurface(player_surface, NULL, hurt_surface, NULL);
    tint(hurt_surface, 100, 100, 100);
    
    //create Spells. SpellID dictates the kind of spell, while the second argument is for damageModifiers like Characterinteligents or gear
    
    spells.push_back(new Spell(SPELL_DASH, 1, current_level));
    spells.push_back(new Spell(SPELL_PUSH_BACK, 1, current_level));
    
    for(int i = 0; i < INV_WIDTH * INV_HEIGHT; i++)
    {
        playerItems[i] = {nullptr, i, 0};
    }
}

// Helper function for intersections with other things (xpos & ypos are the players position while the rest are the parameters of the thing trying to compare to)
bool intersectWith(int xpos1, int ypos1, int x, int y, int w, int h)
{
    // Check all corners
    if((xpos1) >= x && (xpos1) <= x + w && (ypos1) >= y && (ypos1) <= y + h) return true;
    if((xpos1 + PLAYER_WIDTH) > x && (xpos1 + PLAYER_WIDTH) < x + w && (ypos1) > y && (ypos1) <= y + h) return true;
    if((xpos1) >= x && (xpos1) <= x + w && (ypos1 + PLAYER_HEIGHT) > y && (ypos1 + PLAYER_HEIGHT) < y + h) return true;
    if((xpos1 + PLAYER_WIDTH) > x && (xpos1 + PLAYER_WIDTH) < x + w && (ypos1 + PLAYER_HEIGHT) > y && (ypos1 + PLAYER_HEIGHT) < y + h) return true;
    return false;
}

#define MARGIN 4 // Player is that much smaller in all directions

bool Player::isInside(float dx, float dy)
{
    if(data.x_pos + dx < 0 || data.x_pos + dx >= TILE_SIZE * current_level->width || data.y_pos + dy < 0 || data.y_pos + dy >= TILE_SIZE * current_level->height) return true; // Out of bounds = you cant walk

    // Check all points of interest
    for(int point_index = 0; point_index < 4; point_index++)
    {
        // Get the position to check based on the point index
        float player_x_offset = dx + MARGIN + (PLAYER_WIDTH - 2 * MARGIN) * (point_index % 2);
        float player_y_offset = dy + MARGIN + (PLAYER_HEIGHT - 2 * MARGIN) * (int)(point_index / 2);
        
        // Check collision with tiles and buildings
        if(current_level->getTile((int)((data.x_pos + player_x_offset) / TILE_SIZE), (int)((data.y_pos + player_y_offset) / TILE_SIZE)).data.tileZ != _z) return true;
        if(current_level->getBuildingCollision(data.x_pos + player_x_offset, data.y_pos + player_y_offset)) return true;

        // Test point at index point_index with all entities
        for(size_t i = 0; i < current_level->entities.size(); i++)
        {
            auto *entity = current_level->entities[i]; // We don't know it's type (Slime, Item, ...)
            
            
            Enemy *enemy = dynamic_cast<Enemy*>(entity);
            Projectile *projectile = dynamic_cast<Projectile*>(entity);
            EntityItem *item = dynamic_cast<EntityItem*>(entity);
            
            if(item != nullptr) continue;
            
            if(enemy != nullptr && enemy->isAlive)
            {
                // TODO
                if(enemy->collision(data.x_pos + player_x_offset, data.y_pos + player_y_offset)) return true;
            }
            else if(projectile != nullptr)
            {
                // Currently no collision with a projectile
            }
            else if(intersectWith((int)(data.x_pos + player_x_offset), (int)(data.y_pos + player_y_offset), (int) entity->data.x_pos, (int) entity->data.y_pos, (int) entity->data.width, (int) entity->data.height)) return true;
        }
    }
    
    for(size_t i = 0; i < current_level->entities.size(); i++)
    {
        auto *entity = current_level->entities[i]; // We don't know it's type (Slime, Item, ...)
        
        // No collision for this entity, skip it
        EntityItem *item = dynamic_cast<EntityItem*>(entity);
        
        if(item != nullptr)
        {
            if(item->data.x_pos + item->data.width >= data.x_pos + dx && item->data.x_pos <= data.x_pos + dx + PLAYER_WIDTH && item->data.y_pos + item->data.height >= data.y_pos - PLAYER_HEIGHT + dy && item->data.y_pos <= data.y_pos + dy + 2 * PLAYER_HEIGHT)
            {
                item->pickUp(); // Send the item the message we picked it up
                current_level->removeEntity(item);
            }
        }
    }
    
    return false;
}

void Player::checkForEntityInteraction()
{
    for(int point_index = 0; point_index < 6 ; point_index++)
    {
        // Get the position to check based on the point index
        float player_x_offset = ((float) PLAYER_WIDTH) * (point_index % 2);
        float player_y_offset = ((float) PLAYER_HEIGHT) * (int)(point_index / 3) - PLAYER_HEIGHT;
        
        for(size_t i = 0; i < current_level->entities.size(); i++)
        {
            auto *entity = current_level->entities[i]; // We don't know its type (Slime, Item, ...)
            //if not relevant dont check
            if(PLAYER_DIST(entity, this) < max(2 * PLAYER_HEIGHT, max(entity->data.width,entity->data.height)))
            {
                Enemy *enemy = dynamic_cast<Enemy*>(entity);
                   
                if(enemy != nullptr && enemy->isAlive)
                {
                   // TODO
                   int damage = enemy->checkForDamage(data.x_pos + player_x_offset, data.y_pos + player_y_offset);
                   if(damage != 0)
                   {
                       takeDamage((float) damage);
                   }
                }
            }
        }
    }
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
    if(walking && !serverPlayer) correctMovement(dx, dy);
    else isInside(0, 0);
    
    if(dx > 0) direction = RIGHT;
    else if(dx < 0) direction = LEFT;
    else if(dy > 0) direction = DOWN;
    else if(dy < 0) direction = UP;
    
    float movement_amount = LENGTH(dx, dy); // Length of vector
    if(movement_amount >= SPEED && (dx != 0 && dy != 0))
    {
        dx /= movement_amount / (float) SPEED;
        dy /= movement_amount / (float) SPEED;
    }
    
    data.x_pos += dx;
    data.y_pos += dy;
    
    if(data.x_pos < 0) data.x_pos = 0;
    if(data.y_pos < 0) data.y_pos = 0;
    if(data.x_pos >= (current_level->width - 1) * TILE_SIZE) data.x_pos = (float)((current_level->width - 1) * TILE_SIZE);
    if(data.y_pos >= (current_level->height - 1) * TILE_SIZE) data.y_pos = (float)((current_level->height - 1) * TILE_SIZE);
    
    _x = data.x_pos;
    _y = data.y_pos;
    
    if(_x <= ((GAME_WIDTH + PLAYER_WIDTH) / 2))
    {
        _x = ((GAME_WIDTH + PLAYER_WIDTH) / 2);
        xoff = (int)(((GAME_WIDTH + PLAYER_WIDTH) / 2) - data.x_pos);
    }
    else if(_x >= current_level->width * TILE_SIZE - ((GAME_WIDTH - PLAYER_WIDTH) / 2))
    {
        _x = (float) current_level->width * TILE_SIZE - ((GAME_WIDTH - PLAYER_WIDTH) / 2.0f);
        xoff = (int)(current_level->width * TILE_SIZE - ((GAME_WIDTH - PLAYER_WIDTH) / 2) - data.x_pos);
    }
    
    if(_y < ((GAME_HEIGHT + PLAYER_HEIGHT) / 2))
    {
        _y = ((GAME_HEIGHT + PLAYER_HEIGHT) / 2);
        yoff = (int)(((GAME_HEIGHT + PLAYER_HEIGHT) / 2) - data.y_pos);
    }
    else if(_y >= current_level->height * TILE_SIZE - ((GAME_HEIGHT - PLAYER_HEIGHT) / 2))
    {
        _y = (float) current_level->height * TILE_SIZE - ((GAME_HEIGHT - PLAYER_HEIGHT) / 2.0f);
        yoff = (int)(current_level->height * TILE_SIZE - ((GAME_HEIGHT - PLAYER_HEIGHT) / 2) - data.y_pos);
    }
}

void Player::moveTo(float x, float y)
{
    data.x_pos = x;
    data.y_pos = y;
    xoff = 0;
    yoff = 0;
    
    if(data.x_pos < 0) data.x_pos = 0;
    if(data.y_pos < 0) data.y_pos = 0;
    if(data.x_pos >= (current_level->width - 1) * TILE_SIZE) data.x_pos = (float)((current_level->width - 1) * TILE_SIZE);
    if(data.y_pos >= (current_level->height - 1) * TILE_SIZE) data.y_pos = (float)((current_level->height - 1) * TILE_SIZE);
    
    _x = data.x_pos;
    _y = data.y_pos;
    
    if(_x <= ((GAME_WIDTH + PLAYER_WIDTH) / 2))
    {
        _x = ((GAME_WIDTH + PLAYER_WIDTH) / 2);
        xoff = (int)(((GAME_WIDTH + PLAYER_WIDTH) / 2) - data.x_pos);
    }
    else if(_x >= current_level->width * TILE_SIZE - ((GAME_WIDTH - PLAYER_WIDTH) / 2))
    {
        _x = (float) current_level->width * TILE_SIZE - ((GAME_WIDTH - PLAYER_WIDTH) / 2.0f);
        xoff = (int)(current_level->width * TILE_SIZE - ((GAME_WIDTH - PLAYER_WIDTH) / 2) - data.x_pos);
    }
    
    if(_y < ((GAME_HEIGHT + PLAYER_HEIGHT) / 2))
    {
        _y = ((GAME_HEIGHT + PLAYER_HEIGHT) / 2);
        yoff = (int)(((GAME_HEIGHT + PLAYER_HEIGHT) / 2) - data.y_pos);
    }
    else if(_y >= current_level->height * TILE_SIZE - ((GAME_HEIGHT - PLAYER_HEIGHT) / 2))
    {
        _y = (float) current_level->height * TILE_SIZE - ((GAME_HEIGHT - PLAYER_HEIGHT) / 2.0f);
        yoff = (int)(current_level->height * TILE_SIZE - ((GAME_HEIGHT - PLAYER_HEIGHT) / 2) - data.y_pos);
    }
    
}

void Player::render(int x, int y)
{
    for (int i = 0; i < (int) spells.size(); i++) 
	{
        if (!spells[i]->renderOverPlayer) 
		{
            spells[i]->render();
        }
    }
    
    if(!texture.id)
    {
        texture = getTexture(player_surface);
        
        glUseProgram(light_shader);
        glActiveTexture(GL_TEXTURE0 + 1);
        glUniform1i(glGetUniformLocation(light_shader, "player_texture"), 1);
        glBindTexture(GL_TEXTURE_2D, texture.id);
    }
    if(texture_hurt.id == 0) texture_hurt = getTexture(hurt_surface);
    

    //animation speed scales with player speed
    if(walking && (timer++ * SPEED) >= 45)
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

    SDL_Rect src = {32 * anim, (animSet * 4 + direction) * 64 + 1, 32, 64};
    SDL_Rect dst = {PLAYER_OFFSET_X - xoff, PLAYER_OFFSET_Y - yoff - PLAYER_HEIGHT, PLAYER_WIDTH, 128};
    if(graceLeft > 0)
    {
        graceLeft = graceLeft - 1;
        !blinkTimer ? blinkTimer = blinkDuration : blinkTimer--;
        blinkTimer > blinkDuration / 2? renderWithShading(texture_hurt, src, dst):renderWithShading(texture, src, dst);
        
    }
    else
    {
        renderWithShading(texture, src, dst);
    }
    renderStats(xoff, yoff);
    
    // fillRect(0xFFFF00FF, {(int) PLAYER_OFFSET_X-xoff + MARGIN, (int) PLAYER_OFFSET_Y-PLAYER_HEIGHT-yoff + MARGIN, PLAYER_WIDTH - 2 * MARGIN, PLAYER_HEIGHT*2 - 2 * MARGIN});
    
    //render spells
    for (int i = 0; i < (int) spells.size(); i++) 
	{
        if (spells[i]->renderOverPlayer) 
		{
            spells[i]->render();
        }
    }
}

void Player::renderStats(int xoff, int yoff)
{
    if((animationHealth <= 0 || currentHealth == maxHealth) && currentMana == maxMana) return; // Dead or full health
    
    if(animationHealth != currentHealth)
    {
        if (currentHealth != lastHealth) {
            lastHealth = currentHealth;
            hpDifference = currentHealth - animationHealth;
            hpBarTicks = 30;
        }
        float step = hpDifference / 30.0f;
        if (hpBarTicks > 0) {
            hpBarTicks--;
            animationHealth += step;
        }
    }
    
    if(animationMana != currentMana)
    {
        if (currentMana != lastMana) {
            lastMana = currentMana;
            manaDifference = currentMana - animationMana;
            manaBarTicks = 30;
        }
        float step = manaDifference / 30.0f;
        if (manaBarTicks > 0) {
            manaBarTicks--;
            animationMana += step;
        }
    }
    
    SDL_Rect hpbar = { (int) PLAYER_OFFSET_X - xoff, (int) PLAYER_OFFSET_Y - yoff - 100, (int) TILE_SIZE, 20 };
    
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

void Player::spell(int index)
{
    spells[index]->castSpell(direction);
}


void Player::update(const uint8_t *keys)
{
    //spell update.... i will throw them into a vector.... sometime
    for(int i = 0; i < (int) spells.size(); i++)
    {
        spells[i]->update();
    }
    checkForEntityInteraction();
    
    //the dash ... TODO: add the key to config
    if(keys[SDL_SCANCODE_SPACE]){
        spell(0);
    }
    
    //regen a bit of mana, maybe could be increased by items
    if (currentMana < maxMana) {
        currentMana += 1.0f / 30.0f;
    }else currentMana = maxMana;
    
}

void Player::addItem(Item *item)
{
    for(int i = 0; i < INV_WIDTH * INV_HEIGHT; i++)
    {
        if(playerItems[i].item != nullptr && *item == playerItems[i].item)
        {
            playerItems[i].item = item;
            ++playerItems[i].amountItems; // Increase amount of items in that slot
            return;
        }
    }
    for(int i = 0; i < INV_WIDTH * INV_HEIGHT; i++)
    {
        if(playerItems[i].item == nullptr)
        {
            playerItems[i].item = item;
            ++playerItems[i].amountItems; // Increase amount of items in that slot
            return;
        }
    }
    
    printf("[ERROR/WARN] No space left in inventory... Dropping the item\n");
    // TODO: drop the item
}
