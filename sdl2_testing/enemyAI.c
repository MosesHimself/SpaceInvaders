
#include "main.h"

void enemyAI(Game *game)  {
    
    Ship *eTmp = game->enemyStartPtr;
    
    while(eTmp != NULL)  {
        
        //count time
        eTmp->i++;
        if( eTmp->fired > 0)  {
            eTmp->fired--;
        }
        
        switch(eTmp->type)  {
                
                
                //
                //first ship type is a brawler
                //flys up close
                //at short random intervals will stray towards player
                //shoots when lined up with player
            case 0:
                
                if(game->player != NULL)  {
                    
                    //shooting
                    if(eTmp->x > game->player->x - 10 && eTmp->x < game->player->x + 10)  {
                        if(eTmp->i % 7 == 3)  {
                            loadProjectile(game, eTmp->x + eTmp->w / 2, eTmp->y + eTmp->h / 2);
                            eTmp->fired += 20;
                        }
                    }
                }
                
                //change direction when at the sides of the screen
                if(eTmp->i % 55 == 4)  {
                    eTmp->dx *= -1;
                }
                
                if(eTmp->i % 1000 == 0)  {
                    eTmp->dy *= -1;
                }
                /*
                 if(eTmp->i % 400 == rand() % 200)  {
                 eTmp->dx *= -1;
                 }
                 */
                break;
                
                
                //
                //sniper ship
                //strafes side to side at top of screen
                //randomly will lock on man and fire rapidly
            case 1:
                
                if(eTmp->i % 1000 == 0)  {
                    eTmp->dx *= -1;
                }
                
                if(eTmp->i % 400 == 4)  {
                    Projectile *projPtr = loadProjectile(game, eTmp->x, eTmp->y);
                    eTmp->fired += 30;
                    projPtr->w = 20;
                    projPtr->h = 20;
                    projPtr->damage = 50;
                    if(eTmp->x > game->player->x)  {
                        projPtr->dx = (eTmp->x - game->player->x)/-60;
                    }
                    else if(eTmp->x < game->player->x)  {
                        projPtr->dx = (game->player->x - eTmp->x)/60;
                    }
                    if(eTmp->y > game->player->y)  {
                        projPtr->dy = (eTmp->y - game->player->y)/60;
                    }
                    else if(eTmp->y < game->player->y)  {
                        projPtr->dy = (game->player->y - eTmp->y)/60;
                    }
                }
                break;
                /*
            case 2:
                
                if(eTmp->i % 1000 == 0)  {
                    eTmp->dx *= -1;
                }
                
                if(eTmp->i % 400 == 4)  {
                    Projectile *projPtr = loadProjectile(game, eTmp->x, eTmp->y);
                    eTmp->fired += 30;
                    projPtr->w = 20;
                    projPtr->h = 20;
                    projPtr->damage = 50;
                    if(eTmp->x > game->player->x)  {
                        projPtr->dx = (eTmp->x - game->player->x)/-60;
                    }
                    else if(eTmp->x < game->player->x)  {
                        projPtr->dx = (game->player->x - eTmp->x)/60;
                    }
                    if(eTmp->y > game->player->y)  {
                        projPtr->dy = (eTmp->y - game->player->y)/60;
                    }
                    else if(eTmp->y < game->player->y)  {
                        projPtr->dy = (game->player->y - eTmp->y)/60;
                    }
                }
                break;
                 */
            default:
                
                break;
        }
        
        eTmp->dy += eTmp->ddy;
        eTmp->y += eTmp->dy;
        
        eTmp->dx += eTmp->ddx;
        eTmp->x += eTmp->dx;
        
        eTmp = eTmp->next;
        
        
    }
    
}