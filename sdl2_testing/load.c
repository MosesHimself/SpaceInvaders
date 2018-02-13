

#include "SDL.h"
#include <stdio.h>
#include "main.h"


void load(Game *game)  {
        
    
    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
    TTF_Init();
    
    game->screen = malloc(sizeof(Screen));
    
    game->screen->height = 850;
    game->screen->width = 1400;
    
    //Create an application window with the following settings:
    game->window = SDL_CreateWindow("GANG GANG GANG GANG",              // window title
                                    SDL_WINDOWPOS_UNDEFINED,            // initial x position
                                    SDL_WINDOWPOS_UNDEFINED,            // initial y position
                                    game->screen->width,                // width, in pixels
                                    game->screen->height,               // height, in pixels
                                    0                                   // flags
                                    );
    
    
    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //create renderer using hardware acceleration and stuff
    
    SDL_RenderSetLogicalSize(game->renderer, game->screen->width, game->screen->height);
    //sets logical size for pixels on screen
    
    game->numStars = 100;
    
    
    game->starStartPtr = NULL;
    
    int i;
    //load the stars so they can appear before game
    for(i = 0; i < game->numStars; i++)  {
        loadStars(game);
    }
    
    //game->screen->numSquares = 0;
    
    
    //SDL_RenderClear(game->renderer);
    
    loadFonts(game);
    
    game->intro = malloc(sizeof(Intro));
    
    intro(game);
    
    if(game->playingState == 42)  {
        return;
    }
    
    //loadRender(game);
    
    
    
    
    //loadGame(game);
    
}



void loadImages(Game *game)  {
    
    SDL_Surface *surface = NULL;
    
    
    surface = IMG_Load("shot2_1.png");
    if(surface == NULL)
    {
        printf("Cannot find man_lta.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    game->projectile[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
    
    surface = IMG_Load("shot_1.png");
    if(surface == NULL)
    {
        printf("Cannot find man_lta.png!\n\n");
        SDL_Quit();
        exit(1);
    }
    game->projectile[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);
}

void loadFonts(Game *game)  {
    
    //Load fonts
    game->screen->font0 = TTF_OpenFont("astronaut.regular.ttf", 96);
    if(game->screen->font0 == NULL)
    {
        printf("Cannot find font file1!\n\n");
        SDL_Quit();
        exit(1);
    }

    
    
}

void loadRender(Game* game)  {
    
    SDL_SetRenderDrawColor(game->renderer, 100 , 100 , 100 , 255);
    
    
    SDL_RenderClear(game->renderer);

    
    SDL_Rect loadRect = {game->screen->width/2 - game->intro->loadW/2, game->screen->height/2 - game->intro->loadH/2, game->intro->loadW, game->intro->loadH};
    SDL_RenderCopy(game->renderer, game->intro->loadText, NULL, &loadRect);
    
    SDL_RenderPresent(game->renderer);

}

void loadStars(Game *game)  {
    
    //create node and set values
    Star *node = malloc(sizeof(Star));
    Star *tmp = game->starStartPtr;
    
    node->h = rand() % 10 * 0.5;
    node->w = node->h;
    
    node->timer = 0;
    
    node->x = rand() % game->screen->width;
    node->y = rand() % game->screen->height;
    
    node->dy = rand() % 10 * 0.4 + 10;
    
    node->rgb[0] = 204 + rand() % 52;
    node->rgb[1] = 204 + rand() % 52;
    node->rgb[2] = 204 + rand() % 52;
    
    node->next = NULL;
    
    
    
    //if the list is empty place at top of list
    if(tmp == NULL)  {
        game->starStartPtr = node;
        return;
    }
    //else traverse till end of list is found
    else while(tmp->next != NULL)  {
        tmp = tmp->next;
    }
    if(tmp->next == NULL)  {
        tmp->next = node;
    }
    
}

void loadGame(Game* game)  {
    
    //Loading screen render
    
    loadPlayer(game);
    //loadImages(game);
    loadHUD(game);
    
    game->enemyStartPtr = NULL;
    game->partStartPtr = NULL;
    game->projStartPtr = NULL;
    
    game->death = malloc(sizeof(Death));
    
    game->death->deathCount = 0;
    game->lives = 3;
    
    game->time = 0;
    game->score = 0;
    game->level = 1;
    game->dScore = 0;
    game->numFrames = 0;
    
    FILE *fptr = fopen("scoreboard.txt", "r");
    if(fptr == NULL)  {
        printf("File error\n");
        game->playingState = 0;
        return;
    }
    
    fscanf(fptr, "%d", &(game->highScore));
    
    fclose(fptr);
    
    game->screen->effectsCounter = 0;
    

    game->numLoadedE = 0;
    game->numEnemies = 0;
    

    
}

void loadHUD(Game *game)  {
    
    
    
    sprintf(game->screen->score, "Score:%d",game->score);
    sprintf(game->screen->level, "%d:Level",game->level);
    sprintf(game->screen->life, "Health:");
    sprintf(game->screen->enemies, "%d:Enemies",game->numLoadedE);
    sprintf(game->screen->health, "%d",game->player->lifeHold);

    /*
    SDL_Color neonYellow = { 243, 243, 21, 255};
    //SDL_Color neonOrange = { 255, 153, 51, 255};
    //SDL_Color neonGreen = { 193, 253, 51, 255};
    SDL_Color neonBlue = { 13, 213, 252, 255};
    SDL_Color neonPink = { 252, 90, 184, 255};
    */
    
    float i = game->player->x / 200;
    int rgb[3];
    int j = 35;
    
    rgb[0] = 127 * cos(j + i + (3.14159 * 2)) + 128;
    rgb[1] = 127 * sin(j + i + (3.14159 * 2)) + 128;
    rgb[2] = 127 * cos(j + i + 3.14159) + 128;
    SDL_Color cycle = {rgb[0] , rgb[1] , rgb[2] , 255};
    SDL_Color black = { 0, 0, 0, 255};

    
    
    SDL_Surface *tmp = TTF_RenderText_Blended(game->screen->font0, game->screen->life, cycle);
    game->screen->lifeText = SDL_CreateTextureFromSurface(game->renderer, tmp);
    
    game->screen->lifeH = tmp->h;
    game->screen->lifeW = tmp->w;
    
    SDL_FreeSurface(tmp);
    
    SDL_Surface *tmp1 = TTF_RenderText_Blended(game->screen->font0, game->screen->score, cycle);
    game->screen->scoreText = SDL_CreateTextureFromSurface(game->renderer, tmp1);
    
    game->screen->scoreH = tmp1->h;
    game->screen->scoreW = tmp1->w;
    
    SDL_FreeSurface(tmp1);
    
    SDL_Surface *tmp2 = TTF_RenderText_Blended(game->screen->font0, game->screen->level, cycle);
    game->screen->timeText = SDL_CreateTextureFromSurface(game->renderer, tmp2);
    
    game->screen->timeH = tmp2->h;
    game->screen->timeW = tmp2->w;
    
    SDL_FreeSurface(tmp2);
    
    SDL_Surface *tmp3 = TTF_RenderText_Blended(game->screen->font0, game->screen->health, black);
    game->screen->healthText = SDL_CreateTextureFromSurface(game->renderer, tmp3);
    
    game->screen->healthH = tmp3->h;
    game->screen->healthW = tmp3->w;
    
    SDL_FreeSurface(tmp3);
    
    
    
    SDL_Surface *tmp4 = TTF_RenderText_Blended(game->screen->font0, game->screen->enemies, cycle);
    game->screen->enemiesText = SDL_CreateTextureFromSurface(game->renderer, tmp4);
    
    game->screen->enemiesH = tmp4->h;
    game->screen->enemiesW = tmp4->w;
    
    SDL_FreeSurface(tmp4);
    /*
    SDL_Surface *tmp5 = TTF_RenderText_Blended(game->font0, game->screen->points, neonYellow);
    game->screen->pointsText = SDL_CreateTextureFromSurface(game->renderer, tmp5);
    
    game->screen->pointsH = tmp5->h;
    game->screen->pointsW = tmp5->w;
    
    SDL_FreeSurface(tmp5);
    */
}

void loadPlayer(Game *game)  {
 
    game->player = malloc(sizeof(Ship));
    
    game->player->x = game->screen->width / 2;
    game->player->y = game->screen->height/2;

    game->player->h = 50;
    game->player->w = 50;
    game->player->life = 100;
    game->player->sideState = 0;
    
    game->player->projDelay = 0;
    
    game->player->shotValue = 3;
    
    game->player->shotCount = 0;
    
    game->player->dx = 0;
    game->player->dy = 0;
    game->player->ddx = 0;
    game->player->ddy = 0;
    
    game->player->dLife = 0;
    game->player->lifeHold = game->player->life;

    /*
    game->player->rgb[0] = 200;
    game->player->rgb[1] = 200;
    game->player->rgb[2] = 200;
    */
    
    game->player->next = NULL;
    game->player->weaponStartPtr = NULL;
    
    loadShield(game);
    
}

void removePlayer(Game *game, float y, float x)  {
    
    Ship *tmp = game->player;
    Ship *prev = game->player;
    
    if(game->player == NULL)  {
        return;
    }
    
    free(game->player->shield);
    
    if(game->player->y == y && game->player->x == x)  {
        
        game->player = tmp->next;
        free(tmp);
        return;
        
    }
    
    while(tmp != NULL)  {
        
        prev = tmp;
        tmp = tmp->next;
        if(tmp != NULL)  {
            if(tmp->y == y && tmp->x == x)  {
                prev->next = tmp->next;
                free(tmp);
                
                return;
            }
        }
        
        
    }

}



void loadEnemy(Game *game)  {
    
    
    Ship *node = malloc(sizeof(Ship));
    Ship *tmp = game->enemyStartPtr;

    game->numLoadedE++;

    node->fired = 0;
    
    node->type = rand() % 2;
    
    node->sideState = 1;
    
    node->h = 70;
    node->w = 50;
    
    node->ddx = 0;
    node->dx = 1;
    
    node->ddy = 0;
    if(node->type == 0)
        node->dy = 1;
    else
        node->dy = 0;
    
    node->rgb[0] = rand() % 255;
    node->rgb[1] = rand() % 255;
    node->rgb[2] = rand() % 255;
    
    node->life = 100;
    
    
    node->next = NULL;
    
    node->x = rand() % game->screen->width;
    node->y = rand() % game->screen->height - 40;
    
    if(tmp == NULL)  {
        game->enemyStartPtr = node;
        return;
    }
    
        
    else while(tmp->next != NULL)  {
        tmp = tmp->next;
    }
    if(tmp->next == NULL)  {
        tmp->next = node;
        
    }
    
    
}

void removeEnemy(Game *game, float y, float x)  {
 
    Ship *tmp = game->enemyStartPtr;
    Ship *prev = game->enemyStartPtr;
    
    if(game->enemyStartPtr == NULL)  {
        return;
    }
    
    game->numLoadedE--;
    
    if(game->enemyStartPtr->y == y && game->enemyStartPtr->x == x)  {
        
        tmp = game->enemyStartPtr;
        game->enemyStartPtr = tmp->next;
        free(tmp);
        return;
        
    }
    
    //while(tmp->x != x,)
    
    while(tmp != NULL)  {
        
        prev = tmp;
        tmp = tmp->next;
        if(tmp != NULL)  {
            if(tmp->y == y && tmp->x == x)  {
                prev->next = tmp->next;
                free(tmp);
            
                return;
            }
        }
        
        
    }
    
}

Projectile* loadProjectile(Game *game, float x, float y)  {
    
    float i = game->player->x / 200;
    Projectile *node = malloc(sizeof(Projectile));
    Projectile *tmp = game->projStartPtr;
    
    node->h = 25;
    node->w = 10;

    if(x == -1 && y == -1)  {
        node->x = game->player->x + game->player->w / 2 - node->w/2;
        node->y = game->player->y;
        node->dy = -15;
        node->rgb[0] = game->player->rgb[0];
        node->rgb[1] = game->player->rgb[1];
        node->rgb[2] = game->player->rgb[2];

    }
    else  {
        node->x = x;
        node->y = y;
        node->dy = 10;
        
        node->rgb[0] = 127 * cos(220 + i + (3.14159 * 2)) + 128;
        node->rgb[1] = 127 * sin(220 + i + (3.14159 * 2)) + 128;
        node->rgb[2] = 127 * cos(220 + i + 3.14159) + 128;
    }
    
    
    
    node->damage = 50;
    
    node->dx = 0;
    
        
    node->next = NULL;
    
    if(tmp == NULL)  {
        game->projStartPtr = node;
        return node;
    }
    
    
    else while(tmp->next != NULL)  {
        tmp = tmp->next;
    }
    if(tmp->next == NULL)  {
        tmp->next = node;
        
    }

    return node;
    
}

void removeProjectile(Game *game, float y, float x)  {
    
    Projectile* tmp;
    tmp = game->projStartPtr;
    Projectile* prev = NULL;
    
    if(tmp == NULL)  {
        return;
    }
    
    if(game->projStartPtr->y == y && game->projStartPtr->x == x)  {
        
        tmp = game->projStartPtr;
        game->projStartPtr = tmp->next;
        free(tmp);
        return;
        
    }
    
    //while(tmp->x != x,)
    
    while(tmp != NULL)  {
        if(tmp->y == y && tmp->x == x)  {
            prev->next = tmp->next;
            free(tmp);
            
            return;
        }
        
        prev = tmp;
        tmp = tmp->next;
        
    }
    
    
    
}

void explosion(Game *game, float x, float y)  {
    //x = rand() % 1280;
    //y = rand() % 800;
    
    int i;
    
    for(i = 0; i < 40; i++)  {
        loadParticle(game, x, y);
    }
}

void loadParticle(Game *game, float x, float y)  {
    
    Particle *tmp = game->partStartPtr;
    Particle *node = NULL;
    
    int flipx;
    int flipy;
    
    flipy = rand() % 2;
    flipx = rand() % 2;
    
    node = malloc(sizeof(Particle));
    
    node->h = rand() % 25 + 1;
    node->w = node->h;
    node->rgb[0] = 255;
    node->rgb[1] = 255;
    node->rgb[2] = 255;
    node->dy = rand() % 9;
    node->dx = rand() % 9;
    
    if(flipx == 0)  {
        node->dx = node->dx * -1;
    }
    
    if(flipy == 0)  {
        node->dy = node->dy * -1;
    }
    
    
    
    node->y =y;
    node->x =x;
    
    node->next = NULL;
    
    node->next = NULL;
    
    if(tmp == NULL)  {
        game->partStartPtr = node;
        return;
    }
    
    
    else while(tmp->next != NULL)  {
        tmp = tmp->next;
    }
    if(tmp->next == NULL)  {
        tmp->next = node;
        
    }
    
    
}

void removeParticle(Game *game, float y, float x)  {
    
    Particle* tmp;
    tmp = game->partStartPtr;
    Particle* prev = NULL;
    
    if(game->partStartPtr->y == y && game->partStartPtr->x == x)  {
        
        tmp = game->partStartPtr;
        game->partStartPtr = tmp->next;
        free(tmp);
        return;
        
    }
    
    //while(tmp->x != x,)
    
    while(tmp != NULL)  {
        if(tmp->y == y && tmp->x == x)  {
            prev->next = tmp->next;
            free(tmp);
            
            return;
        }
        
        prev = tmp;
        tmp = tmp->next;
        
    }
    
    
    
}

void loadShield(Game *game)  {

    game->player->shield = malloc(sizeof(Shield));
    
    game->player->shield->h = 10;
    game->player->shield->w = 100;

    game->player->shield->rgb[0] = game->player->rgb[0];
    game->player->shield->rgb[1] = game->player->rgb[1];
    game->player->shield->rgb[2] = game->player->rgb[2];

    
    
}




