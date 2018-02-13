

#include "main.h"

void collisionDetect(Game *game)  {
    
    enemyCollision(game);
    playerCollision(game);
    if(game->player != NULL)  {
        if(game->player->shieldUp)
            shieldCollision(game);
    }
}

void playerCollision(Game *game)  {
    
    if(game->player->y > 800 - game->player->h)  {
        game->player->dy = 0;
        game->player->ddy = 0;
        game->player->y = 800 - game->player->h;

    }
    
    if(game->player->y < 0)  {
        game->player->dy = 0;
        game->player->ddy = 0;
        game->player->y = 0;
        
    }
    
    if(game->player->x > game->screen->width - game->player->h)  {
        game->player->ddx = 0;
        game->player->dx *= -0.5;
        game->player->x = game->screen->width - game->player->h;
        
    }
    
    if(game->player->x < 0)  {
        game->player->ddx = 0;
        game->player->dx *= -0.5;
        game->player->x = 0;
        
    }
    
    //projCollision(game, game->player);
    
    Projectile* tmp = game->projStartPtr;
    
    Ship *ship = game->player;
    
    float b1, b2, t1, t2, l1,l2, r1, r2;
    
    b1 = ship->y + ship->h;
    t1 = ship->y;
    l1 = ship->x;
    r1 = ship->x + ship->w;
    
    while(tmp != NULL)  {
        
        if(game->player == NULL || game->projStartPtr == NULL)  {
            return;
        }
        
        b2 = tmp->y + tmp->h;
        t2 = tmp->y;
        l2 = tmp->x;
        r2 = tmp->x + tmp->w;
        
        
        if((l1 < r2) && (r1 > l2) && (t1 < b2) && (b1 > t2) && (tmp->dy > 0))  {
            
            explosion(game, ship->x + ship->w/2, ship->y + ship->h/2);
            ship->dLife += 25;
            ship->life -= 25;
            game->screen->effectsCounter = 15;

            
            
            tmp = tmp->next;
            
            
            if(ship->life < 1)   {
                death(game);
                //game->dScore -= 500;
                //game->screen->effectsCounter = 15;
                
            }
            
            removeProjectile(game, t2, l2);
            
            return;
        }
        
        if(tmp != NULL)  {
            tmp = tmp->next;
        }
    }

    
}

void enemyCollision(Game *game)  {
    
    Ship* ship = game->enemyStartPtr;
    
    
    
    while(ship != NULL)  {
        
        if(ship->y > 500)  {
            ship->y = 500;
            ship->dy *= 1;
        }
        if(ship->x < 0)  {
            if(ship->dx < 0)
                ship->dx *= -1;
            ship->x = 0;
            
        }
        
        if(ship->y < 0)  {
            if(ship->dy < 0)
                ship->dy *= -1;
            ship->y = 0;
            
        }
        if(ship->x > game->screen->width - ship->w)  {
            if(ship->dx > 0)
                ship->dx *= -1;
            ship->x = game->screen->width - ship->w;
            
        }
        
        ship = projCollision(game, ship);
        
        if(ship != NULL)  {
            
            ship = ship->next;
        }
    }

    
}

Ship* projCollision(Game *game, Ship* ship)  {
    
    
    Projectile* tmp = game->projStartPtr;
    
    float b1, b2, t1, t2, l1,l2, r1, r2, i = 0, z = 0, x, y;
    
    b1 = ship->y + ship->h;
    t1 = ship->y;
    l1 = ship->x;
    r1 = ship->x + ship->w;
    
    while(tmp != NULL)  {
        
        b2 = tmp->y + tmp->h;
        t2 = tmp->y;
        l2 = tmp->x;
        r2 = tmp->x + tmp->w;
        
        
        
        if((l1 < r2) && (r1 > l2) && (t1 < b2) && (b1 > t2) && (tmp->dy < 0))  {
            
            explosion(game, ship->x + ship->w/2, ship->y + ship->h/2);
            ship->life -= tmp->damage;
            z = ship->life;
            ship->y -= 5;
            y = ship->y;
            x = ship->x;
            //ship->ddy = 1;
            
            ship = ship->next;
            tmp = tmp->next;
            
            
            if(z < 1)   {
                removeEnemy(game, y, x);
                game->dScore += 500;
                
            }
            
            removeProjectile(game, t2, l2);
            
            i++;
            
        }
        else if(ship == game->player)  {
            
            explosion(game, ship->x - ship->w, ship->y + ship->h);
            ship->life -= tmp->damage;
            z = ship->life;
            
            //ship->ddy = 1;
            
            //ship = ship->next;
            //tmp = tmp->next;
            
            
            if(z < 1)   {
                death(game);
                //game->dScore -= 500;
                //game->screen->effectsCounter = 15;
                
            }
            
            removeProjectile(game, t2, l2);
            
            return NULL;
            
            //i++;

            
        }
        
        
        if(tmp != NULL)  {
            tmp = tmp->next;
        }
    }
    if(i == 1)  {
        return game->enemyStartPtr;
        
    }
    else return ship;
    
}

void shieldCollision(Game *game)  {
    
    Projectile* tmp = game->projStartPtr;
    
    float b1, b2, t1, t2, l1,l2, r1, r2;
    
    b1 = game->player->shield->y + game->player->shield->h;
    t1 = game->player->shield->y;
    l1 = game->player->shield->x;
    r1 = game->player->shield->x + game->player->shield->w;
    
    while(tmp != NULL)  {
        
        b2 = tmp->y + tmp->h;
        t2 = tmp->y;
        l2 = tmp->x;
        r2 = tmp->x + tmp->w;
        
        
        if((l1 < r2) && (r1 > l2) && (t1 < b2) && (b1 > t2) && (tmp->dy > 0))  {
            
            
            tmp->dy *= -1;
            tmp->rgb[0] = game->player->rgb[0];
            tmp->rgb[1] = game->player->rgb[1];
            tmp->rgb[2] = game->player->rgb[2];

            
        }
        
            tmp = tmp->next;
        
        
        
    }
    
    
}

