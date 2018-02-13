

#include <stdio.h>
#include "main.h"

void freeGame(Game *game)  {
 
    SDL_DestroyTexture(game->intro->creditText);
    SDL_DestroyTexture(game->intro->titleText);
    SDL_DestroyTexture(game->intro->startText);
    SDL_DestroyTexture(game->intro->quitText);
     
    
    
    
    
    
    SDL_DestroyTexture(game->screen->lifeText);
    SDL_DestroyTexture(game->screen->enemiesText);
    SDL_DestroyTexture(game->screen->scoreText);
    SDL_DestroyTexture(game->screen->timeText);
    
    
    
    freeEnemies(game);
    freeProjectiles(game);
    freeParticles(game);
    
    free(game->death);
    
    
    game->starStartPtr = NULL;
    
    free(game->player);
    
    
    

    TTF_CloseFont(game->intro->font);
    TTF_CloseFont(game->screen->font0);
    
    
    free(game->intro);
    
}

void freeStars(Game *game)  {
    
    Star *tmp = game->starStartPtr;
    
    Star *prev = NULL;
    
    while(tmp != NULL)  {
        prev = tmp;
        tmp = tmp->next;
        free(prev);
    }
    
    game->starStartPtr = NULL;
    
}

void freeEnemies(Game *game)  {
    Ship *tmp = game->enemyStartPtr;
    
    Ship *prev = NULL;
    
    while(tmp != NULL)  {
        prev = tmp;
        tmp = tmp->next;
        free(tmp);
    }
    
    game->enemyStartPtr = NULL;
}

void freeProjectiles(Game *game)  {
    Projectile *tmp = game->projStartPtr;
    
    Projectile *prev = NULL;
    
    while(tmp != NULL)  {
        prev = tmp;
        tmp = tmp->next;
        free(tmp);
    }
    
    game->projStartPtr = NULL;
}

void freeParticles(Game *game)  {
    Particle *tmp = game->partStartPtr;
    
    Particle *prev = NULL;
    
    while(tmp != NULL)  {
        prev = tmp;
        tmp = tmp->next;
        free(tmp);
    }

    game->partStartPtr = NULL;
}