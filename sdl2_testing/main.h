

#ifndef sdl2_testing_main_h
#define sdl2_testing_main_h


#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

typedef struct _intro  {
    
    char title[30];
    char credit[20];
    char start[20];
    char quit[20];
    char load[15];
    
    SDL_Texture *titleText;
    SDL_Texture *creditText;
    SDL_Texture *startText;
    SDL_Texture *quitText;
    SDL_Texture *loadText;
    
    int titleY;
    int creditY;
    int titleDY;
    int creditDY;
    
    int titleX;
    int creditX;
    int titleDX;
    int creditDX;
    
    int startX;
    int quitX;
    int startDX;
    int quitDX;
    
    int startY;
    int quitY;
    int startDY;
    int quitDY;
    
    int titleH, titleW;
    int creditH, creditW;
    int startH, startW;
    int quitH, quitW;
    int loadH, loadW;
    
    TTF_Font *font;
    
    
    int timer;

    
} Intro;

typedef struct _death  {
    
    char death[25];
    char lives[25];
    char timer[25];
    char over[25];
    char load[25];
    char oldScore[25];
    char newScore[25];
    char highScore[25];


    
    SDL_Texture *deathText;
    SDL_Texture *livesText;
    SDL_Texture *timerText;
    SDL_Texture *overText;
    SDL_Texture *loadText;
    SDL_Texture *newScoreText;
    SDL_Texture *oldScoreText;
    SDL_Texture *highScoreText;



    
    int deathH, deathW;
    int livesH, livesW;
    int timerH, timerW;
    int overH, overW;
    int loadH, loadW;
    int newScoreH, newScoreW;
    int oldScoreH, oldScoreW;
    int highScoreH, highScoreW;


    
    int deathCount;
    
} Death;


typedef struct _star  {
    
    float h, w;
    
    int timer;
    
    float x, y;
    float dx, dy;
    
    int rgb[3];
    
    struct _star *next;
    
} Star;


typedef struct _particle  {
    
    int h, w;
    int x, y;
    int dx, dy;
    
    int timer;
    
    int rgb[3];         //rgb values
    
    struct _particle *next;
    
} Particle;

typedef struct _projectile  {
    
    int h, w;
    float x, y;
    float dx, dy;
    
    int damage;
    
    int timer;
    
    int rgb[3];         //rgb values
    
    struct _projectile *next;
    
} Projectile;

typedef struct _weapon  {
    
    char* name;
    
    int damage;
    int numBullets;     //how many bulllets this weapon has til running out
    int delay;          //delay between firing
    
    int projH;          //height of projectile it fires
    int projW;          //width of projectile it fires
    int projDX;         //velocity of the proj
    int projDY;         //velocity of the proj
    int type;
    
    Projectile *projStartPtr;
    
    struct _weapon *next;
    
} Weapon;

typedef struct _shield  {
    
    int h, w;
    int x, y;
    
    int timer;
    int fullTime;
    int countdown;
    int rgb[3];
    
    int health;
    
} Shield;

typedef struct _ship  {
    
    char* name;
    
    
    int timer;
    int life;
    int dLife;
    int lifeHold;
    int sideState;      //(0:freindly 1:foe) determines which type of projectiles can affect it
    
    int shotCount;
    int shotValue;
    
    int shieldUp;
    
    int fired;
    
    int projDelay;
    
    float x, dx;     //x position, change in x(velocity), change in velocity(acceleration)
    float y, dy;     //y position, change in y(velocity), change in velocity(acceleration)
    float ddx, ddy;
    int h;              //height
    int w;              //width
    
    int rgb[3];         //rgb values
    
    Weapon *weaponStartPtr;     //start to the weapon link list
    
    int type;
    
    int i;
    
    Shield *shield;
    
    struct _ship *next;         //for linked list to string together ships
    
} Ship;

typedef struct _screen  {
    
    TTF_Font *font0;
    TTF_Font *font1;
    TTF_Font *font2;
    
    int height, width;
    
    int rgb[3];
    
    int effectsCounter;
    
    int numSquares;
    
    char score[15];
    char life[15];
    char level[15];
    char enemies[15];
    char weapon[15];
    char health[20];
    
   
    
    SDL_Texture *scoreText;
    SDL_Texture *lifeText;
    SDL_Texture *weaponText;
    SDL_Texture *timeText;
    SDL_Texture *loadText;
    SDL_Texture *bgText;
    SDL_Texture *framesText;
    SDL_Texture *enemiesText;
    SDL_Texture *pointsText;
    SDL_Texture *healthText;
    
    int lifeH, lifeW;
    int scoreH, scoreW;
    int timeH, timeW;
    int weaponH, weaponW;
    int framesH, framesW;
    int pointsH, pointsW;
    int enemiesH, enemiesW;
    int healthH, healthW;

    
} Screen;

typedef struct _game  {
    
    
    long time;               //time keeping value, resets at 10,000
    int level;
    long numFrames;          //num of frames passes
    int playingState;       //(0:not 1:yes)
    int score, dScore, highScore;      //change in score
    int numStars;
    int lives;
        
    int numEnemies;         //how many enemies there should be
    int numLoadedE;         //how many enemies are loaded on screen
    
    TTF_Font *font0;
    TTF_Font *font1;
    TTF_Font *font2;
    
    Projectile *projStartPtr;
    Particle *partStartPtr;
    
    Ship *enemyStartPtr;
    Ship *player;           //player pointer
    
    Star *starStartPtr;
    Star *lineStart;
    Screen *screen;
    
    //SDL crap
    SDL_Window *window;
    SDL_Renderer *renderer;
    
    Intro *intro;
    
    Death *death;
    
    SDL_Texture *projectile[2];
    
    
    
    //start of link list for multiple games
    //maybe for levels, not sure
    struct _game *nextGame;
    
} Game;

bool gameLoop();

void load(Game *game);
void loadImages(Game *game);
void loadFonts(Game *game);
void loadRender(Game *game);
void loadStars(Game *game);
void loadGame(Game *game);
void loadHUD(Game *game);
void loadPlayer(Game *game);
void removePlayer(Game *game, float y, float x);
void loadEnemy(Game *game);
void removeEnemy(Game *game, float y, float x);
Projectile* loadProjectile(Game *game, float x, float y);
void removeProjectile(Game *game, float y, float x);
void explosion(Game *game, float x, float y);
void loadParticle(Game *game, float x, float y);
void removeParticle(Game *game, float y, float x);
void loadShield(Game *game);
void removeShield(Game *game);



void intro(Game *game);
void introLoad(Game *game);
int introInput(Game *game);
void introProcess(Game *game);
void introRender(Game *game);


void render(Game *game);
Star* renderStars(Game *game);
void renderHUD(Game *game);
void renderPlayer(Game *game);
void renderEnemy(Game *game);
void renderProjectile(Game *game);
void renderParticle(Game *game);
void renderShield(Game *game);

void update(Game *game);
void updateStars(Game *game);
void updatePlayer(Game *game);
void updateEnemy(Game *game);
void updateProjectile(Game *game);
void updateParticle(Game* game);

int recieveInput(Game *game);

void collisionDetect(Game *game);
void playerCollision(Game *game);
void enemyCollision(Game *game);
Ship* projCollision(Game *game, Ship* ship);
void shieldCollision(Game *game);

void freeGame(Game *game);
void freeStars(Game *game);
void freeEnemies(Game *game);
void freeProjectiles(Game *game);
void freeParticles(Game *game);

void death(Game *game);
void deathLoad(Game *game);
void deathInput(Game *game);
void deathProcess(Game *game);
void deathRender(Game *game);

void enemyAI(Game *game);


#endif
