
#include "main.h"
#include <math.h>

void update(Game *game)  {
    
    game->numEnemies = (int)game->time / 200;
    
    if(game->player->projDelay > 0)  {
        game->player->projDelay--;
    }
    else if(game->player->projDelay == 0)  {
        game->player->shotCount = game->player->shotValue;
    }
    
    if(game->player->dLife > 0)  {
        game->player->lifeHold -= 1;
        game->player->dLife -= 1;
    }
    if(game->player->life < 1)  {
        game->player->life = 0;
    }
    
    if(game->dScore > 0)  {
        game->score += 20;
        game->dScore -= 20;
        //makes score increase by 2 at a time
    }
    
    if(game->screen->effectsCounter != 0)  {
        game->screen->effectsCounter--;
    }
    
    game->time++;
    if(game->time > 2000)  {
        game->time = 0;
        game->level++;
    }
    
    game->numFrames++;
    
    if(game->player != NULL)  {
    
        updatePlayer(game);
        
        
        updateEnemy(game);
        
        if(game->numEnemies > game->numLoadedE)  {
            loadEnemy(game);
        }
        
        
        updateProjectile(game);
        updateParticle(game);
        
    }
    
    updateStars(game);
}


void updateStars(Game *game)  {
    
    
       
    
    Star *tmp = game->starStartPtr;
    
    while(tmp != NULL)  {
        tmp->y += tmp->dy;
        //tmp->h += 0.1;
        tmp->w = tmp->h;

        if(tmp->y > game->screen->height)  {
            tmp->h = rand() % 10 * 0.5;
            tmp->w = tmp->h;
            tmp->y = 0;
            tmp->x = rand() % game->screen->width;
        }
        
        tmp = tmp->next;
    }
    
}


void updatePlayer(Game *game)  {
    
    if(game->player != NULL)  {
    
        float i = game->player->x / 200;
        
        
        game->player->ddy += 0.6;
        
        if(game->player->ddy < -2)  {
            game->player->ddy = -2;
        }
        if(game->player->ddy > 2)  {
            game->player->ddy = 2;
            
        }
        
        game->player->shield->x = game->player->x + game->player->w/2 - game->player->shield->w/2;
        game->player->shield->y = game->player->y - 30;
        game->player->shield->rgb[0] = game->player->rgb[0];
        game->player->shield->rgb[1] = game->player->rgb[1];
        game->player->shield->rgb[2] = game->player->rgb[2];
        
        //update x & y position, velocity, and acceleration
        //limits on velocity
        game->player->dy += game->player->ddy;
        
        if(game->player->dy > 10)  {
            game->player->dy = 10;
        }
        
        if(game->player->dy < -5)  {
            game->player->dy = -5;
        }
        
        game->player->y += game->player->dy;
        
        game->player->dx += game->player->ddx;
        
        if(game->player->dx > 6)  {
            game->player->dx = 6;
        }
        if(game->player->dx < -6)  {
            game->player->dx = -6;
        }
        
        game->player->x += game->player->dx;
        
        int j = 35;
        
        game->player->rgb[0] = 127 * cos(j + i + (3.14159 * 2)) + 128;
        game->player->rgb[1] = 127 * sin(j + i + (3.14159 * 2)) + 128;
        game->player->rgb[2] = 127 * cos(j + i + 3.14159) + 128;
        
    }
    
}

void updateEnemy(Game *game)  {

    enemyAI(game);

}

void updateProjectile(Game *game)  {
    
    Projectile *tmp = game->projStartPtr;
    float y, x, z = 0;
    
    while(tmp != NULL)  {
        
        if(tmp->x < 0 || tmp->x > game->screen->width)  {
            
            tmp->dx *= -1;
            
        }
        
        if(tmp->y < 0 || tmp->y > 1400)  {
            y = tmp->y;
            x = tmp->x;
            
            tmp->dx = 0;
            tmp->dy = 0;
            
            z = 1;
            tmp = tmp->next;
            removeProjectile(game, y, x);
        }
        else  {
            tmp->x += tmp->dx;
            tmp->y += tmp->dy;
            tmp = tmp->next;
        }
    }
    


    
}

void updateParticle(Game *game)  {
    Particle *tmp  = game->partStartPtr;
    
    float y, x, z = 0;
    
    while(tmp != NULL)  {
        
        tmp->timer++;
        if(tmp->timer > 1200)  {
            tmp->timer = 0;
        }
        /*
        if(tmp->timer > 10)  {
            y = tmp->y;
            x = tmp->x;
            
            tmp->dx = 0;
            tmp->dy = 0;
            
            z = 1;
            tmp = tmp->next;
            removeParticle(game, y, x);
            return;
        }
        */
        if(tmp->y < 0 || tmp->y > game->screen->height)  {
            
            tmp->dy *= -1;
            
        }
        if(tmp->x < 0 || tmp->x > game->screen->width)  {
            
            tmp->dx *= -1;
            
        }
            
            
        if(tmp->h == 0)  {
            y = tmp->y;
            x = tmp->x;
            
            tmp->dx = 0;
            tmp->dy = 0;
            
            z = 1;
            tmp = tmp->next;
            removeParticle(game, y, x);
        }
        else  {
            
            tmp->x += tmp->dx;
            tmp->y += tmp->dy;
            if(game->time % 2 == 0)  {
                tmp->h--;
            }
            tmp->w = tmp->h;
            
            tmp = tmp->next;
            
        }
    }
    
    
    

    
}