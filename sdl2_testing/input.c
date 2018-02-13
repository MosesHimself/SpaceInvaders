
#include "main.h"


int recieveInput(Game *game)  {
    
    SDL_Event event;
    
    
    while(SDL_PollEvent(&event))
    {
        switch(event.type)  {
            case SDL_WINDOWEVENT_CLOSE:  {
                if(game->window)  {
                    SDL_DestroyWindow(game->window);
                    return 0;
                }
            }
                break;
            case SDL_KEYDOWN:  {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        return 0;
                        
                        break;
                    case SDLK_SPACE:
                        if(!game->player->shieldUp && game->player->shotCount > 0)  {
                            
                            game->player->shotCount--;
                            game->player->projDelay = 20;
                            loadProjectile(game, -1, -1);
                        }
                        
                        break;
                    case SDLK_RSHIFT:
                        
                        loadEnemy(game);
                        
                        break;
                        
                    case SDLK_DOWN:
                        //explosion(game, 1, 1);
                        //game->player->ddy += 5;
                        
                        break;
                    case SDLK_UP:
                        
                        //game->player->ddy -= 50;
                        
                        break;
                    case SDLK_TAB:
                        //freeGame(game);
                        break;
                    case SDLK_RETURN:
                        
                        break;
                        
                    default:
                        
                        break;
                }
            }
                break;
            /*
            case SDL_KEYUP:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        
                        if( game->player->ddx < 0 )
                            game->player->ddx = 0;
                        break;
                    case SDLK_RIGHT:
                        if( game->player->ddx > 0 )
                            //game->player->ddx = 0;
                        break;
                    case SDLK_UP:
                        if( game->player->ddy < 0 )
                            game->player->ddy = 0;
                        
                        break;
                    case SDLK_DOWN:
                        if( game->player->shieldUp == 1 )
                            game->player->shieldUp = 0;
                        break;
                    default:
                        
                        game->player->ddy = 0;
                        game->player->ddx = 0;
                        
                        game->player->shieldUp = 0;
                        
                        //friction
                        if(game->player->dx > 0.2 || game->player->dx < -0.2)  {
                            game->player->dx *= 0.97;
                        }
                        else
                            game->player->dx = 0;
                        break;
                }
                break;
             */
        
        
            case SDL_QUIT:
                return 0;
                break;
        }
    }
    
    //More jumping
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    
    int i = 0, j = 0, k = 0;
    
   
    
    if(state[SDL_SCANCODE_DOWN])
    {
        game->player->shieldUp = 1;
        i = 1;
        
    }
    if(state[SDL_SCANCODE_UP])
    {
        game->player->ddy = -1;

    }
    
    //Walking
    if(state[SDL_SCANCODE_LEFT])
    {
        j = 1;
        game->player->ddx = -1;
        
    }
    if(state[SDL_SCANCODE_RIGHT])
    {
        j = 1;
        game->player->ddx = 1;

    }
    
    
      //no input from user
        //game->player->ddy = 0;
    if(j == 0)  {
        
        
                //friction

        game->player->ddx = 0;
        if(game->player->dx > 0.2 || game->player->dx < -0.2)  {
            game->player->dx *= 0.97;
        }
        else
            game->player->dx = 0;
    }
    
    
        if(i == 0)
        game->player->shieldUp = 0;
        
        
        
    
    
    return 1;
}