//
//  death.c
//  game
//
//  Created by H.G. King on 8/25/16.
//  Copyright © 2016 Mike Farrell. All rights reserved.
//

#include "main.h"

void death(Game *game)  {
    
    game->screen->effectsCounter = 0;
    game->death->deathCount = 200;
    
    game->lives--;
    
    if(game->lives == 0)  {
        game->death->deathCount = 400;
    }
    
    //remove player
    removePlayer(game, game->player->y, game->player->x);
    
    freeEnemies(game);
    freeProjectiles(game);
    freeParticles(game);
    
    game->time = game->numLoadedE = 0;
    
    
    //load words
    deathLoad(game);
    
    while(game->death->deathCount != 0 && game->playingState != 0)  {
        
        
        
        if(game->death->deathCount != 0)  {
            
            deathInput(game);
            //process
            if(game->death->deathCount != 0)  {
                updateStars(game);
                
                //render
                //render(game);
                deathRender(game);
                
                SDL_DestroyTexture(game->death->deathText);
                SDL_DestroyTexture(game->death->livesText);
                SDL_DestroyTexture(game->death->timerText);
                SDL_DestroyTexture(game->death->overText);
                SDL_DestroyTexture(game->death->newScoreText);
                SDL_DestroyTexture(game->death->oldScoreText);
                SDL_DestroyTexture(game->death->highScoreText);
            }
        }
        
    }
    //load player
    if(game->lives != 0)  {
        loadPlayer(game);
    }
    else  {
        game->playingState = 0;
    }
    
    
    
    
    game->score += game->dScore;
    game->dScore = 0;
    
}

void deathLoad(Game *game)  {
    
    

    sprintf(game->death->death, "You Died !");
    sprintf(game->death->lives, "Lives %d",game->lives);
    sprintf(game->death->timer, "%d to respawn", game->death->deathCount / 20);
    sprintf(game->death->over, "Game over !");
    sprintf(game->death->newScore, "Score:%d", game->score);
    sprintf(game->death->oldScore, "High:%d", game->highScore);
    sprintf(game->death->highScore, "New High Score!");


    
    
    
    SDL_Color neonYellow = { 243, 243, 21, 255};
    SDL_Color neonOrange = { 255, 153, 51, 255};
    SDL_Color neonGreen = { 193, 253, 51, 255};
    SDL_Color neonBlue = { 13, 213, 252, 255};
    SDL_Color neonPink = { 252, 90, 184, 255};
    
    
    
    SDL_Surface *tmp = TTF_RenderText_Blended(game->intro->font, game->death->death, neonBlue);
    game->death->deathText = SDL_CreateTextureFromSurface(game->renderer, tmp);
    
    game->death->deathH = tmp->h;
    game->death->deathW = tmp->w;
    
    SDL_FreeSurface(tmp);
    
    SDL_Surface *tmp1 = TTF_RenderText_Blended(game->intro->font, game->death->lives, neonGreen);
    game->death->livesText = SDL_CreateTextureFromSurface(game->renderer, tmp1);
    
    game->death->livesH = tmp1->h;
    game->death->livesW = tmp1->w;
    
    SDL_FreeSurface(tmp1);
    
    SDL_Surface *tmp2 = TTF_RenderText_Blended(game->intro->font, game->death->timer, neonPink);
    game->death->timerText = SDL_CreateTextureFromSurface(game->renderer, tmp2);
    
    game->death->timerH = tmp2->h;
    game->death->timerW = tmp2->w;
    
    SDL_FreeSurface(tmp2);
    
    
    SDL_Surface *tmp3 = TTF_RenderText_Blended(game->intro->font, game->death->over, neonPink);
    game->death->overText = SDL_CreateTextureFromSurface(game->renderer, tmp3);
    
    game->death->overH = tmp3->h;
    game->death->overW = tmp3->w;
    
    SDL_FreeSurface(tmp3);
    
    
    SDL_Surface *tmp4 = TTF_RenderText_Blended(game->intro->font, game->death->oldScore, neonYellow);
    game->death->oldScoreText = SDL_CreateTextureFromSurface(game->renderer, tmp4);
    
    game->death->oldScoreH = tmp4->h;
    game->death->oldScoreW = tmp4->w;
    
    SDL_FreeSurface(tmp4);

    SDL_Surface *tmp5 = TTF_RenderText_Blended(game->intro->font, game->death->highScore, neonYellow);
    game->death->highScoreText = SDL_CreateTextureFromSurface(game->renderer, tmp5);
    
    game->death->highScoreH = tmp5->h;
    game->death->highScoreW = tmp5->w;
    
    SDL_FreeSurface(tmp5);

    SDL_Surface *tmp6 = TTF_RenderText_Blended(game->intro->font, game->death->newScore, neonYellow);
    game->death->newScoreText = SDL_CreateTextureFromSurface(game->renderer, tmp6);
    
    game->death->newScoreH = tmp6->h;
    game->death->newScoreW = tmp6->w;
    
    SDL_FreeSurface(tmp6);

    
    
    


}

void deathInput(Game *game)  {
    
    SDL_Event event;
    
    
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_WINDOWEVENT_CLOSE:
            {
                if(game->window)
                {
                    SDL_DestroyWindow(game->window);
                    
                    game->playingState = 0;
                }
            }
                break;
            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        game->playingState = 0;
                        
                        break;
                    case SDLK_RETURN:
                        game->playingState = 1;
                        game->death->deathCount = 0;
                        
                        
                        break;
                        
                    default:
                        
                        break;
                }
            }
                break;
            case SDL_QUIT:
                game->playingState = 0;
                break;
        }
    }
    
}

void deathRender(Game *game)  {
    
    
    
    if(game->death->deathCount != 0)  {
        game->death->deathCount--;
    }

    
    deathLoad(game);
    
    SDL_SetRenderDrawColor(game->renderer, 10 , 10 , 10 , 255);
    
    
    SDL_RenderClear(game->renderer);
    
    if(game->lives == 0)  {
        
        if(game->death->deathCount < 200)  {
            SDL_Rect oldScoreRect = {700 - game->death->oldScoreW/2, 100 - game->death->oldScoreH/2 , game->death->oldScoreW, game->death->oldScoreH};
            SDL_RenderCopy(game->renderer, game->death->oldScoreText, NULL, &oldScoreRect);
            
            SDL_Rect newScoreRect = { 700 - game->death->newScoreW/2, 300 - game->death->newScoreH/2, game->death->newScoreW, game->death->newScoreH};
            SDL_RenderCopy(game->renderer, game->death->newScoreText, NULL, &newScoreRect);
            
            if(game->score > game->highScore)  {
            
            SDL_Rect highScoreRect = { 700 - game->death->highScoreW/2, 500 - game->death->highScoreH/2, game->death->highScoreW, game->death->highScoreH};
            SDL_RenderCopy(game->renderer, game->death->highScoreText, NULL, &highScoreRect);
                
            }
        }

        if(game->death->deathCount >= 200)  {
            SDL_Rect overRect = {game->screen->width / 2 - game->death->overW / 2, game->screen->height / 2 - game->death->overH / 2, game->death->overW, game->death->overH};
            
            SDL_RenderCopy(game->renderer, game->death->overText, NULL, &overRect);
        }

    }
    else  {
    
        SDL_Rect deathRect = {700 - game->death->deathW/2, 100 - game->death->deathH/2 , game->death->deathW, game->death->deathH};
        SDL_RenderCopy(game->renderer, game->death->deathText, NULL, &deathRect);

        SDL_Rect livesRect = { 700 - game->death->livesW/2, 300 - game->death->livesH/2, game->death->livesW, game->death->livesH};
        SDL_RenderCopy(game->renderer, game->death->livesText, NULL, &livesRect);
        
        SDL_Rect timerRect = { 700 - game->death->timerW/2, 500 - game->death->timerH/2, game->death->timerW, game->death->timerH};
        SDL_RenderCopy(game->renderer, game->death->timerText, NULL, &timerRect);

    }
    renderStars(game);
    
    SDL_RenderPresent(game->renderer);

    
}
