
#include "main.h"

void render(Game *game)  {
    
    /*
    float i = game->player->x / 200;
    int rgb[3];
    
    rgb[0] = 127 * cos(128 + i + (3.14159 * 2)) + 128;
    rgb[1] = 127 * sin(128 + i + (3.14159 * 2)) + 128;
    rgb[2] = 127 * cos(128 + i + 3.14159) + 128;
     
    
    SDL_SetRenderDrawColor(game->renderer, rgb[0] , rgb[1] , rgb[2] , 255);
    */
    
    SDL_SetRenderDrawColor(game->renderer, 0, 0 , 0 , 255);

    if(game->screen->effectsCounter == 0)  {
        SDL_RenderClear(game->renderer);
    }
    
    
    
    Star *tmp = game->lineStart;
    
    while(tmp != NULL)  {
        
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 0);
        
        SDL_Rect rect = {tmp->x, tmp->y, tmp->w, tmp->h };
        
        SDL_RenderFillRect(game->renderer, &rect);
        tmp = tmp->next;
    }
    
    Star *sTmp = renderStars(game);
    
    if(game->player != NULL)  {
        renderHUD(game);
        renderEnemy(game);
        renderPlayer(game);
        renderProjectile(game);
        renderParticle(game);
        
        if(game->player->shieldUp == 1)  {
            renderShield(game);
        }
        
    }
    
    
    int i = 0;
    
    while(i < 50 && sTmp != NULL)  {
        
        SDL_SetRenderDrawColor(game->renderer, sTmp->rgb[0], sTmp->rgb[1], sTmp->rgb[2], 0);
                SDL_Rect rect = {sTmp->x, sTmp->y, sTmp->w, sTmp->h };
        
        SDL_RenderFillRect(game->renderer, &rect);
        
        sTmp = sTmp->next;
    }

    
    
    SDL_RenderPresent(game->renderer);
    
    SDL_DestroyTexture(game->screen->lifeText);
    SDL_DestroyTexture(game->screen->enemiesText);
    SDL_DestroyTexture(game->screen->scoreText);
    SDL_DestroyTexture(game->screen->timeText);
    SDL_DestroyTexture(game->screen->healthText);
    
}

Star* renderStars(Game *game)  {
    
    Star *tmp = game->starStartPtr;
    
    while(tmp != NULL && game->numStars > 50)  {
        
        SDL_SetRenderDrawColor(game->renderer, tmp->rgb[0], tmp->rgb[1], tmp->rgb[2], 0);
        /*
        float i = game->player->x / 200;
        int rgb[3];
        
        rgb[0] = 127 * cos(64 + i + (3.14159 * 2)) + 128;
        rgb[1] = 127 * sin(64 + i + (3.14159 * 2)) + 128;
        rgb[2] = 127 * cos(64 + i + 3.14159) + 128;

        
        
        SDL_SetRenderDrawColor(game->renderer, rgb[0] , rgb[1] , rgb[2] , 255);
        */
        
        SDL_Rect rect = {tmp->x, tmp->y, tmp->w, tmp->h };
        
        SDL_RenderFillRect(game->renderer, &rect);
        
        tmp = tmp->next;
        game->numStars--;
    }
    game->numStars = 100;
    return tmp;
}

void renderHUD(Game *game)  {
    
    
    SDL_DestroyTexture(game->screen->lifeText);
    SDL_DestroyTexture(game->screen->enemiesText);
    SDL_DestroyTexture(game->screen->scoreText);
    SDL_DestroyTexture(game->screen->timeText);
    
    loadHUD(game);
    
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    
    SDL_Rect rect = {309, 9, 302, 57};
    
    SDL_RenderFillRect(game->renderer, &rect);
    
    
    SDL_SetRenderDrawColor(game->renderer, 0, 255, 0, 255);
    
    SDL_Rect bottomRect = {310, 10, game->player->lifeHold * 3, 55 };
    
    SDL_RenderFillRect(game->renderer, &bottomRect);

    
    SDL_Rect lifeRect = { 10, -20, game->screen->lifeW, game->screen->lifeH};
    SDL_RenderCopy(game->renderer, game->screen->lifeText, NULL, &lifeRect);

    
    
    SDL_Rect scoreRect = { 10, -50 + game->screen->lifeH, game->screen->scoreW, game->screen->scoreH};
    SDL_RenderCopy(game->renderer, game->screen->scoreText, NULL, &scoreRect);
    
    
    
    SDL_Rect timeRect = { game->screen->width - game->screen->timeW - 10 , -20, game->screen->timeW, game->screen->timeH};
    SDL_RenderCopy(game->renderer, game->screen->timeText, NULL, &timeRect);
    
    
    
    SDL_Rect enemieRect = { game->screen->width - game->screen->enemiesW - 10, -50 + game->screen->timeH, game->screen->enemiesW, game->screen->enemiesH};
    SDL_RenderCopy(game->renderer, game->screen->enemiesText, NULL, &enemieRect);
    
    
    
    SDL_Rect healthRect = { 310, -20, game->screen->healthW, game->screen->healthH};
    SDL_RenderCopy(game->renderer, game->screen->healthText, NULL, &healthRect);
    
    
    
    
    /*
    SDL_Rect enemiesRect = { 10, 0 , game->screen->enemiesW, game->screen->enemiesH};
    SDL_RenderCopy(game->renderer, game->screen->enemiesText, NULL, &enemiesRect);
    */
}

void renderPlayer(Game *game)  {
    
    
    Ship *shipPtr = game->player;
    
    while(shipPtr != NULL)  {
    
        SDL_SetRenderDrawColor(game->renderer, shipPtr->rgb[0], shipPtr->rgb[1], shipPtr->rgb[2], 255);
    
        //draw a rectangle at man's position
        SDL_Rect rect = {shipPtr->x, shipPtr->y, shipPtr->w, shipPtr->h };
        
        
        //SDL_RenderCopy(game->renderer, game->player.image[game->player.frame], NULL, &rect);
        
        SDL_RenderFillRect(game->renderer, &rect);
        
        shipPtr = shipPtr->next;
    
   }
}


void renderEnemy(Game *game)  {
    
    Ship *shipPtr = game->enemyStartPtr;
    
    while(shipPtr != NULL)  {
        if(shipPtr->fired == 0)  {
            //SDL_SetRenderDrawColor(game->renderer,255,255,255,255);
        }
        else  {
            SDL_SetRenderDrawColor(game->renderer,255,0,0,255);

            SDL_RenderDrawLine(game->renderer,game->player->x + game->player->w/2, game->player->y + game->player->h/2, shipPtr->x + shipPtr->w/2, shipPtr->y + shipPtr->h/2);
        }
        //SDL_SetRenderDrawColor(game->renderer, shipPtr->rgb[0], shipPtr->rgb[1], shipPtr->rgb[2], 255);
        if( game->player != NULL)  {
            
            float i = game->player->x / 200;
            int rgb[3];
            
            
            rgb[0] = 127 * cos(220 + i + (3.14159 * 2)) + 128;
            rgb[1] = 127 * sin(220 + i + (3.14159 * 2)) + 128;
            rgb[2] = 127 * cos(220 + i + 3.14159) + 128;
            
            if(shipPtr->life < 100)  {
                rgb[0] = 255;
                rgb[1] = 255;
                rgb[2] = 255;
                
            }
            
            
            SDL_SetRenderDrawColor(game->renderer, rgb[0] , rgb[1] , rgb[2] , 255);
        }
        else  {
            SDL_SetRenderDrawColor(game->renderer, 100 , 100 , 100 , 255);

        }
        
        //draw a rectangle at man's position
        SDL_Rect rect = {shipPtr->x, shipPtr->y, shipPtr->w, shipPtr->h };
        
        
        //SDL_RenderCopy(game->renderer, game->player.image[game->player.frame], NULL, &rect);
        
        SDL_RenderFillRect(game->renderer, &rect);
        
        
        
        shipPtr = shipPtr->next;
        
    }

}

void renderProjectile(Game *game)  {
    
    Projectile *tmp = game->projStartPtr;
    
    //int i = 0;
    
    while(tmp != NULL)  {
        
        SDL_SetRenderDrawColor(game->renderer, tmp->rgb[0], tmp->rgb[1], tmp->rgb[2], 255);
        
        //draw a rectangle at man's position
        SDL_Rect rect = {tmp->x, tmp->y, tmp->w, tmp->h };
        /*
        if(tmp->dy < 0)  {
            SDL_RenderCopy(game->renderer, game->projectile[1], NULL, &rect);
        }
        else
        SDL_RenderCopy(game->renderer, game->projectile[0], NULL, &rect);
        */
        SDL_RenderFillRect(game->renderer, &rect);
        
        tmp = tmp->next;

    }
    
}

void renderParticle(Game *game)  {
    
    Particle *tmp = game->partStartPtr;
    
    while(tmp != NULL)  {
        
        SDL_SetRenderDrawColor(game->renderer, tmp->rgb[0], tmp->rgb[1], tmp->rgb[2], 255);
        
        //draw a rectangle at particles's position
        SDL_Rect rect = {tmp->x, tmp->y, tmp->w, tmp->h };
        
        
        //SDL_RenderCopy(game->renderer, game->player.image[game->player.frame], NULL, &rect);
        
        SDL_RenderFillRect(game->renderer, &rect);
        
        tmp = tmp->next;
        
    }

}

void renderShield(Game *game)  {
    
    
    
    if(game->player->shield != NULL)  {
        
        SDL_SetRenderDrawColor(game->renderer, game->player->shield->rgb[0], game->player->shield->rgb[1], game->player->shield->rgb[2], 255);
        
        //draw a rectangle at particles's position
        SDL_Rect rect = {game->player->shield->x, game->player->shield->y, game->player->shield->w, game->player->shield->h };
        
        
        //SDL_RenderCopy(game->renderer, game->player.image[game->player.frame], NULL, &rect);
        
        SDL_RenderFillRect(game->renderer, &rect);
        
        
    }

}
