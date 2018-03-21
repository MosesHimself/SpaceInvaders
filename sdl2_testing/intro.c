#include "main.h"

void intro(Game *game)  {
    
    game->intro->font = TTF_OpenFont("astronaut.ii.ttf", 125);
    //load intro
    introLoad(game);
    
    game->playingState = 0;
    game->intro->timer = 0;
    
    game->intro->titleY = game->screen->height/2 - game->intro->titleH/2;
    game->intro->creditY = game->screen->height/2 + game->intro->titleH - game->intro->creditH/2;
    
    game->intro->quitDY = 5;
    game->intro->startDY = 5;
    game->intro->titleDY = -5;
    game->intro->creditDY = -5;
    
    game->intro->creditX = 700 - game->intro->creditW/2;
    game->intro->titleX = game->screen->width/2 - game->intro->titleW/2;
    game->intro->quitX = 700 - game->intro->quitW/2;
    game->intro->startX = game->screen->width/2 - game->intro->startW/2;
    
    


    
    game->intro->startY = game->screen->height/2 - game->intro->startH/2;
    game->intro->quitY = game->screen->height/2 + game->intro->startH - game->intro->quitH/2;
   

    while(game->playingState == 0)  {
        
        //take in input
        game->playingState = introInput(game);
        
        if(game->playingState == 0)  {
            
            //process intro
            introProcess(game);
            
            //render intro
            introRender(game);
        }
        
    }
    
    
    
    
}

void introLoad(Game *game)  {
    

    
    sprintf(game->intro->start, "[ENTER] to START");
    sprintf(game->intro->quit, "[ESCAPE] to QUIT");
    sprintf(game->intro->title, "{CAELESTIS}");
    sprintf(game->intro->credit, "Version 2.1");
    sprintf(game->intro->load, "Loading");
    
    SDL_Color neonYellow = { 243, 243, 21, 255};
    //SDL_Color neonOrange = { 255, 153, 51, 255};
    SDL_Color neonGreen = { 193, 253, 51, 255};
    SDL_Color neonBlue = { 13, 213, 252, 255};
    SDL_Color neonPink = { 252, 90, 184, 255};
     
    /*
    float i = game->player->x / 200;
    int rgb[3];
    int j = 35;
    
    rgb[0] = 127 * cos(j + i + (3.14159 * 2)) + 128;
    rgb[1] = 127 * sin(j + i + (3.14159 * 2)) + 128;
    rgb[2] = 127 * cos(j + i + 3.14159) + 128;
    SDL_Color cycle = {rgb[0] , rgb[1] , rgb[2] , 255};
    */
    
    SDL_Surface *tmp = TTF_RenderText_Blended(game->intro->font, game->intro->title, neonBlue);
    game->intro->titleText = SDL_CreateTextureFromSurface(game->renderer, tmp);
    
    game->intro->titleH = tmp->h;
    game->intro->titleW = tmp->w;
    
    SDL_FreeSurface(tmp);
    
    SDL_Surface *tmp1 = TTF_RenderText_Blended(game->intro->font, game->intro->quit, neonGreen);
    game->intro->quitText = SDL_CreateTextureFromSurface(game->renderer, tmp1);
    
    game->intro->quitH = tmp1->h;
    game->intro->quitW = tmp1->w;
    
    SDL_FreeSurface(tmp1);
    
    SDL_Surface *tmp2 = TTF_RenderText_Blended(game->intro->font, game->intro->credit, neonPink);
    game->intro->creditText = SDL_CreateTextureFromSurface(game->renderer, tmp2);
    
    game->intro->creditH = tmp2->h;
    game->intro->creditW = tmp2->w;
    
    SDL_FreeSurface(tmp2);
    
    SDL_Surface *tmp3 = TTF_RenderText_Blended(game->intro->font, game->intro->load, neonPink);
    game->screen->loadText = SDL_CreateTextureFromSurface(game->renderer, tmp3);
     
    game->intro->loadH = tmp3->h;
    game->intro->loadW = tmp3->w;
     
    SDL_FreeSurface(tmp3);
    
    
    SDL_Surface *tmp4 = TTF_RenderText_Blended(game->intro->font, game->intro->start, neonYellow);
    game->intro->startText = SDL_CreateTextureFromSurface(game->renderer, tmp4);
    
    game->intro->startH = tmp4->h;
    game->intro->startW = tmp4->w;
    
    SDL_FreeSurface(tmp4);

    
    
}

int introInput(Game *game)  {
    
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
                    
                    return 42;
                }
            }
                break;
            case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        return 42;
                        
                        break;
                    case SDLK_RETURN:
                        return 1;
                        
                        
                        break;
                    
                    default:
                        
                        break;
                }
            }
                break;
            case SDL_QUIT:
                return 42;
                break;
        }
    }

    return 0;
}

void introProcess(Game *game)  {
    game->intro->timer++;
    updateStars(game);
    
    if(game->intro->titleY < -5 || (game->intro->creditY + game->intro->creditH) > game->screen->height)  {
        game->intro->titleDY *= -1;
        game->intro->creditDY *= -1;
    }
    
    if(game->intro->startY < -5 || (game->intro->quitY + game->intro->quitH) > game->screen->height)  {
        game->intro->startDY *= -1;
        game->intro->quitDY *= -1;
    }
    
    
    if(game->intro->timer > 200)  {
        game->intro->quitY += game->intro->quitDY;
        game->intro->startY += game->intro->startDY;
        
        

    }
    else  {
        game->intro->titleY += game->intro->titleDY;
        game->intro->creditY += game->intro->creditDY;
    }
    
}

void introRender(Game *game)  {
    
    SDL_SetRenderDrawColor(game->renderer, 10 , 10 , 10 , 255);
    
    SDL_RenderClear(game->renderer);
    
    
    
    if(game->intro->timer < 200)  {
        
        SDL_Rect titleRect = {game->intro->titleX, game->intro->titleY, game->intro->titleW, game->intro->titleH};
        SDL_RenderCopy(game->renderer, game->intro->titleText, NULL, &titleRect);
        
        SDL_Rect creditRect = { game->intro->creditX, game->intro->creditY, game->intro->creditW, game->intro->creditH};
        SDL_RenderCopy(game->renderer, game->intro->creditText, NULL, &creditRect);
        
    }
    else  {
    
        SDL_Rect quitRect = { game->intro->quitX, game->intro->quitY,game->intro->quitW, game->intro->quitH};
        SDL_RenderCopy(game->renderer, game->intro->quitText, NULL, &quitRect);
        
        SDL_Rect startRect = { game->intro->startX, game->intro->startY,game->intro->startW, game->intro->startH};
        SDL_RenderCopy(game->renderer, game->intro->startText, NULL, &startRect);

        
    }
    
    renderStars(game);
    
    SDL_RenderPresent(game->renderer);
    
}
