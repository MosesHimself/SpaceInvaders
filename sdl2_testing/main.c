//this was written by HG King in 2016


#include "SDL.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "main.h"



int main(int argc, char *argv[])  {
    
    srand((int)time(NULL));
    
    bool playing = true;
    
    Game *game = malloc(sizeof(Game));
    
    
    
    load(game);
    
    
    playing = gameLoop(game);
    
    if(game->score > game->highScore)  {
    
        FILE *fptr = fopen("scoreboard.txt", "w");
        if(fptr == NULL)  {
            printf("File error\n");
            game->playingState = 0;
        }
        
        fputc( game->score, fptr );
        //fprintf(fptr,"%d", game->score);
        
        fclose(fptr);
    }
    
    
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    
    //SDL_DestroyTexture(game->intro->loadText);
    //SDL_DestroyTexture(game->projectile[0]);
    //SDL_DestroyTexture(game->projectile[1]);


    SDL_Quit();
    
    TTF_Quit();
    
    freeStars(game);
    
    free(game->screen);

    free(game);

}

bool gameLoop(Game* game)  {
    
    
    loadGame(game);
    
    //game loop
    while(game->playingState == 1)  {
        
        game->playingState = recieveInput(game);
        
        if(game->playingState == 1)  {
            
            update(game);
            
            collisionDetect(game);
            
            render(game);
        }
        
    }
    
    freeGame(game);
    
    if(game->playingState != 0)  {
        return false;
    }
    
    return true;
    
}