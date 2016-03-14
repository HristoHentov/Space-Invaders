#include "includes.h"

SDL_Window * mainWindow = NULL;
SDL_Renderer * mainRenderer = NULL;
TTF_Font * mainFont = NULL;

int times = 0;
int killTarget = -1;
bool tLoaded;
bool init();
bool skip = false;

Uint32 gameTime = 0;


int checkCollision(vector<SDL_Rect>& a, vector<SDL_Rect>& b);

const int gameWidth = 1280;
const int gameHeight = 720;


#include "gameTexture.h"
struct GameTextures
{
    GameTexture pTexLBB;
    GameTexture pTexRBB;
    GameTexture pTexLBT;
    GameTexture pTexLCEB;
    GameTexture pTexLCET;
    GameTexture pTexLCOB;
    GameTexture pTexLCOT;
    GameTexture pTexRBT;
    GameTexture pTexRCEB;
    GameTexture pTexRCET;
    GameTexture pTexRCOB;
    GameTexture pTexRCOT;
};

bool loadMedia(GameTextures&);
void close(GameTextures&);
bool renderScore(int);




bool rendercheck = false;
bool dead = false;
#include "mainShip.h"
#include "shipProtector.h"
#include "mainMonster.h"

#include "monsterGroup.h"
#include "bullet.h"
#include "Projectile.h"

node * head = NULL;
vector<bullet> bulletContainer;
vector<pbullet> pbulletContainer;

GameTexture bgTexture;
GameTexture shipTexture;
GameTexture shipLivesTexture;

GameTexture bulletTexture;
GameTexture MonsterbulletTexture;
GameTexture monsterTypeA;
GameTexture monsterTypeB;
GameTexture monsterTypeC;
GameTexture crashTest;
GameTexture textTexture;
GameTexture destroy;
GameTexture gameOver;
GameTexture youWin;

bool track = false;
int timesGone = 0;
#include "texture.cpp"
#include "protector.cpp"
#include "bullet.cpp"
#include "Projectile.cpp"
#include "ship.cpp"
#include "monster.cpp"
#include "monsterGroup.cpp"


int playerScore = 0;
string playerScoreTX;
int timesPassed = 1;
int shipLives = 3;
int monstersKilled = 0;
int shootlevel = 50;

int main(int argc, char * argv[])
{
    bool firsttime = true;
    ostringstream convert;
    convert << playerScore;
    playerScoreTX = convert.str();
    srand(time(NULL));


    GameTextures a, b, c, d, e;

    int indicator = 0;
    int adder = 150;
    int goSpeed = 30;



    if(!init())
        cout << "\nSDL Failed to Initialize. ERROR: " << SDL_GetError();

    else
    {

        if(!loadMedia(a) || !loadMedia(b) || !loadMedia(c) || !loadMedia(d) || !loadMedia(e))
            cout << "\nLoading media failed. ERROR: " << SDL_GetError();
        else if(!renderScore(36))
            cout << "\nSDL Has Failed to handle text. ERROR: " << SDL_GetError();
        else
        {

            bool quit = false;
            SDL_Event event;
            mainShip ship;
            monsterGroup MOBS;



            shipProtector protectora(150, 515);
            shipProtector protectorb(375, 515);
            shipProtector protectorc(600, 515);
            shipProtector protectord(825, 515);
            shipProtector protectore(1025, 515);


            protectora.setColliders();
            protectorb.setColliders();
            protectorc.setColliders();
            protectord.setColliders();
            protectore.setColliders();

            MOBS.spawn(head);

            while (!quit)
            {



                    while(SDL_PollEvent(&event) != 0)
                    {
                        if(event.type == SDL_QUIT)
                            quit = true;

                        ship.handleEvent(event);
                    }

                   if(!dead && monstersKilled != 55)
                {

                    if(!skip)
                    {

                    ship.moveShip();



                    if(MOBS.getHeading(head))
                    {
                        goSpeed -= 1;
                        if(goSpeed <= 3)
                            goSpeed = 3;
                    }


                    if(indicator % goSpeed == 0)
                    {
                        track = false;
                        MOBS.setDirection(head);
                    }


                    bgTexture.render(0,0);
                    textTexture.render(140, 7);


                    switch(shipLives)
                    {
                    case 3:
                    {
                        shipLivesTexture.render(1045, 0);
                        shipLivesTexture.render(1125, 0);
                        shipLivesTexture.render(1205, 0);
                        break;
                    }

                    case 2:
                    {
                        shipLivesTexture.render(1045, 0);
                        shipLivesTexture.render(1125, 0);
                        break;
                    }
                    case 1:
                    {
                        shipLivesTexture.render(1045, 0);
                        break;
                    }
                    case 0:
                    {
                        gameOver.render(0 , 0);
                        dead = true;
                        break;
                    }



                    }

                    psetColliders(pbulletContainer);
                    setColliders(bulletContainer);
                    ship.setShipColliders();



                    MOBS.setGColliders(head);

                    pfindCollision(pbulletContainer, ship);

                    findCollision(bulletContainer, protectora, MOBS, a);
                    findCollision(bulletContainer, protectorb, MOBS, b);
                    findCollision(bulletContainer, protectorc, MOBS, c);
                    findCollision(bulletContainer, protectord, MOBS, d);
                    findCollision(bulletContainer, protectore, MOBS, e);

                    pfindCColision(pbulletContainer, protectora, a);
                    pfindCColision(pbulletContainer, protectorb, b);
                    pfindCColision(pbulletContainer, protectorc, c);
                    pfindCColision(pbulletContainer, protectord, d);
                    pfindCColision(pbulletContainer, protectore, e);




                    ostringstream convert;
                    convert << playerScore;
                    playerScoreTX = convert.str();
                    renderScore(36);

                    if(shootlevel >= 15)
                    {
                    if(indicator % shootlevel == 0)
                    {
                        int index = rand() % 55 + 1;
                        MOBS.shoot(head, index);
                    }
                    }

                    else if(shootlevel < 15)

                    {
                        if(indicator % 15 == 0)
                    {
                        int index = rand() % 55 + 1;
                        MOBS.shoot(head, index);
                    }
                    }


                    ship.render();
                    protectora.renderProtector(1, killTarget, a);
                    protectorb.renderProtector(2 , -1, b);
                    protectorc.renderProtector(3, -1, c);
                    protectord.renderProtector(4, -1, d);
                    protectore.renderProtector(5, -1, e);






                    MOBS.renderMGroup(head);


                    renderBullet(bulletContainer, 0);
                    prenderBullet(pbulletContainer, 0);



                    if(indicator % 120 == 0)
                        cout << "\nYour Score : " << playerScore;

                    SDL_RenderPresent(mainRenderer); // RENDER ALL TO FRONT BUFFER
                    indicator++;

                }

                }
                else if(dead)
                {
                    const Uint32 timeEntered = SDL_GetTicks();
                    SDL_RenderClear(mainRenderer);
                    gameOver.render(0,0);
                    SDL_RenderPresent(mainRenderer);


                    if(SDL_GetTicks() - 6000 == timeEntered)
                        quit = true;
                    else
                        skip = true;


                }

                else if(monstersKilled >= 55)
                {
                    if(firsttime)
                    {
                        int tempscore = 1000;
                        tempscore = tempscore / (SDL_GetTicks() / 1000);

                        playerScore = playerScore + (tempscore * 25);
                        ostringstream convert;
                        convert << playerScore;
                        playerScoreTX = convert.str();
                        firsttime = false;
                    }

                    else
                {

                    const Uint32 timeEntered = SDL_GetTicks();
                    SDL_RenderClear(mainRenderer);
                    youWin.render(0, 0);

                    renderScore(100);
                    textTexture.render(570, 590);
                    SDL_RenderPresent(mainRenderer);

                    skip = true;
                }

                }

            }

        }
    }
    close(a);
    close(b);
    close(c);
    close(d);
    close(e);
    return 0;
}


void findCollision(vector<bullet> &currentProt, shipProtector &currentPT, monsterGroup &NPC, GameTextures & currentPRT)
{
    bool voidHit = true;
    bool stop = false;
    bool deadBullet = false;
    int cNumA = 50;
    int bulletSize = currentProt.size();

    for (int i = 0; i < bulletSize; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if(checkCollision(currentPT.getColliders(cNumA), currentProt[i].getCollider()) > -1)
            {
                cNumA = checkCollision(currentPT.getColliders(j), currentProt[i].getCollider());
                currentPT.destroyProtectorEl(cNumA, currentPRT);
                currentProt.erase(currentProt.begin() + i);
                voidHit = false;
                stop = true;
            }

            if(!voidHit)
                break;
        }


        if(!stop)
        {

            node * temp;
            temp = head;
            while(temp)
            {

                if(checkCollision(temp -> currentMonster -> getCollider(), currentProt[i].getCollider()) > - 1)
                {
                    if(temp -> nodeIndex > 33)
                        playerScore += 10;
                    else if(temp -> nodeIndex > 11 &&  temp -> nodeIndex < 34)
                        playerScore += 20;
                    else if(temp -> nodeIndex > 0 && temp -> nodeIndex < 12)
                        playerScore += 40;

                    currentProt.erase(currentProt.begin() + i);
                    temp -> renderFLAG = true;
                    temp -> moveFLAG = false;
                    temp -> currentMonster -> clearCollider();
                    voidHit = false;
                    monstersKilled++;
                    shootlevel -= 1;
                }

                if(!voidHit)
                    break;


                temp = temp -> next;

            }
        }

        if(voidHit)
            if(killBulletAtEnd(currentProt[i].getCollider()))
                currentProt.erase(currentProt.begin() + i);






    }
}


void pfindCollision(vector<pbullet> &currentProjectile, mainShip ship)
{
    int pvoidHit = true;
    int pbulletSize = currentProjectile.size();

    for (int i = 0; i < pbulletSize; i++)
    {
        if(checkCollision(ship.getColliders(), currentProjectile[i].pgetCollider()) > -1)
        {
            shipLives -= 1;
            currentProjectile.erase(currentProjectile.begin() + i);
        }
    }
}


void pfindCColision(vector<pbullet> &currentProjectile, shipProtector &currentProtector, GameTextures & currentPRT)
{
    int pvoidHit = true;
    int pbulletSize = currentProjectile.size();
    int cIndex;

    for (int i = 0; i < pbulletSize; i++)
    {
        for(int j = 0; j < 12; j++)
        {

            if(checkCollision(currentProtector.getColliders(j), currentProjectile[i].pgetCollider()) > -1)
            {
                cIndex = checkCollision(currentProtector.getColliders(j), currentProjectile[i].pgetCollider());
                currentProtector.destroyProtectorEl(cIndex, currentPRT);
                currentProjectile.erase(currentProjectile.begin() + i);
            }

        }
    }
}





int checkCollision(vector<SDL_Rect>& a, vector<SDL_Rect>& b)
{
    int result = -1;
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;


    for( int Abox = 0; Abox < a.size(); Abox++ )
    {
        leftA = a[ Abox ].x;
        rightA = a[ Abox ].x + a[ Abox ].w;
        topA = a[ Abox ].y;
        bottomA = a[ Abox ].y + a[ Abox ].h;

        for( int Bbox = 0; Bbox < b.size(); Bbox++ )
        {
            leftB = b[ Bbox ].x;
            rightB = b[ Bbox ].x + b[ Bbox ].w;
            topB = b[ Bbox ].y;
            bottomB = b[ Bbox ].y + b[ Bbox ].h;


            if( ( ( bottomA <= topB ) || ( topA >= bottomB ) || ( rightA <= leftB ) || ( leftA >= rightB ) ) == false )
            {
                result = Abox;
            }

        }
    }


    return result;

}




bool init()
{
    bool working = true;

    if(SDL_Init(SDL_INIT_VIDEO))
    {
        cout << "\nSDL Video Subsystem failed. ERROR: " << SDL_GetError();
        working = false;
    }
    else
    {
        mainWindow = SDL_CreateWindow("Space Invaders v1.2.5", ((1920 - gameWidth) / 2), ((1080 - gameHeight) / 2), gameWidth, gameHeight, SDL_WINDOW_SHOWN);
        if(!mainWindow)
        {
            cout << "\nFailed to create main game window. ERROR: " << SDL_GetError();
            working = false;
        }
        else
        {
            mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(!mainRenderer)
            {
                cout << "\nFailed to initialize renderer. ERROR: " << SDL_GetError();
                working = false;
            }
            else
            {
                SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF);


                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags))
                {
                    cout << "\nSDL_image PNG module failed to initialize.Error: " << IMG_GetError();
                    working = false;
                }

                if(TTF_Init() == -1)
                {
                    cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError();
                    working = false;
                }
            }
        }
    }
    return working;
}

bool loadMedia(GameTextures& one)
{
    bool loaded = true;

    if(!bgTexture.loadFromFile("_img/mainBG.png"))
    {
        cout << "\nFailed to load BG texture. ERROR: " << SDL_GetError();
        loaded = false;
    }

    if(!shipTexture.loadFromFile("_img/ship.png"))
    {
        cout << "\nFailed to load ship texture. ERROR: " << SDL_GetError();
        loaded = false;
    }

    if(!shipLivesTexture.loadFromFile("_img/shipLives.png"))
    {
        cout << "\nFailed to load crashTest texture ERROR: " << SDL_GetError();
        loaded = false;
    }





    if(!one.pTexLBB.loadFromFile("_img/protectorLBB.png"))
    {
        cout << "\nFailed to load ship protector texture ERROR: " << SDL_GetError();
        loaded = false;
    }
    if(!one.pTexLBT.loadFromFile("_img/protectorLBT.png"))
    {
        cout << "\nFailed to load ship protector texture ERROR: " << SDL_GetError();
        loaded = false;
    }
    if(!one.pTexLCEB.loadFromFile("_img/protectorLCEB.png"))
    {
        cout << "\nFailed to load ship protector texture ERROR: " << SDL_GetError();
        loaded = false;
    }
    if(!one.pTexLCET.loadFromFile("_img/protectorLCET.png"))
    {
        cout << "\nFailed to load ship protector texture ERROR: " << SDL_GetError();
        loaded = false;
    }
    if(!one.pTexLCOB.loadFromFile("_img/protectorLCOB.png"))
    {
        cout << "\nFailed to load ship protector texture ERROR: " << SDL_GetError();
        loaded = false;
    }
    if(!one.pTexLCOT.loadFromFile("_img/protectorLCOT.png"))
    {
        cout << "\nFailed to load ship protector texture ERROR: " << SDL_GetError();
        loaded = false;
    }
    if(!one.pTexRBB.loadFromFile("_img/protectorRBB.png"))
    {
        cout << "\nFailed to load ship protector texture ERROR: " << SDL_GetError();
        loaded = false;
    }

    if(!one.pTexRBT.loadFromFile("_img/protectorRBT.png"))
    {
        cout << "\nFailed to load ship protector texture ERROR: " << SDL_GetError();
        loaded = false;
    }
    if(!one.pTexRCEB.loadFromFile("_img/protectorRCEB.png"))
    {
        cout << "\nFailed to load ship protector texture ERROR: " << SDL_GetError();
        loaded = false;
    }
    if(!one.pTexRCET.loadFromFile("_img/protectorRCET.png"))
    {
        cout << "\nFailed to load ship protector texture ERROR: " << SDL_GetError();
        loaded = false;
    }
    if(!one.pTexRCOB.loadFromFile("_img/protectorRCOB.png"))
    {
        cout << "\nFailed to load ship protector texture ERROR: " << SDL_GetError();
        loaded = false;
    }
    if(!one.pTexRCOT.loadFromFile("_img/protectorRCOT.png"))
    {
        cout << "\nFailed to load ship protector texture ERROR: " << SDL_GetError();
        loaded = false;
    }




    if(!bulletTexture.loadFromFile("_img/bullet.png"))
    {
        cout << "\nFailed to load bullet texture ERROR: " << SDL_GetError();
        loaded = false;
    }

    if(!MonsterbulletTexture.loadFromFile("_img/monsterBullet.png"))
    {
        cout << "\nFailed to load monster bullet texture ERROR: " << SDL_GetError();
        loaded = false;
    }




    if(!monsterTypeA.loadFromFile("_img/monsterTypeA.png"))
    {
        cout << "\nFailed to load monsterA texture ERROR: " << SDL_GetError();
        loaded = false;
    }
    if(!monsterTypeB.loadFromFile("_img/monsterTypeB.png"))
    {
        cout << "\nFailed to load monsterB texture ERROR: " << SDL_GetError();
        loaded = false;
    }
    if(!monsterTypeC.loadFromFile("_img/monsterTypeC.png"))
    {
        cout << "\nFailed to load monsterC texture ERROR: " << SDL_GetError();
        loaded = false;
    }




    if(!crashTest.loadFromFile("_img/crashTest.png"))
    {
        cout << "\nFailed to load crashTest texture ERROR: " << SDL_GetError();
        loaded = false;
    }


    if(!gameOver.loadFromFile("_img/GameOver.png"))
    {
        cout << "\nFailed to load GameOver texture ERROR: " << SDL_GetError();
        loaded = false;
    }

    if(!youWin.loadFromFile("_img/YouWin.png"))
    {
        cout << "\nFailed to load GameOver texture ERROR: " << SDL_GetError();
        loaded = false;
    }


    return loaded;
}

bool renderScore()
{
    tLoaded = true;
    mainFont = TTF_OpenFont("_font/Dolce Vita.ttf", 36);
    if(!mainFont)
    {
        cout << "\nFailed to load Dolce Vita FONT! Error: " << TTF_GetError();
        tLoaded = false;
    }
    else
    {
        SDL_Color textColor = {115, 228, 39};
        if(!textTexture.loadFromRenderedText(playerScoreTX, textColor))
        {
            cout << "\nFailed to render text texture!";
            tLoaded = false;
        }
    }

    TTF_CloseFont(mainFont);

    return tLoaded;
}

bool renderScore(int fontSize)
{
    tLoaded = true;
    mainFont = TTF_OpenFont("_font/Dolce Vita.ttf", fontSize);
    if(!mainFont)
    {
        cout << "\nFailed to load Dolce Vita FONT! Error: " << TTF_GetError();
        tLoaded = false;
    }
    else
    {
        SDL_Color textColor = {115, 228, 39};
        if(!textTexture.loadFromRenderedText(playerScoreTX, textColor))
        {
            cout << "\nFailed to render text texture!";
            tLoaded = false;
        }
    }

    TTF_CloseFont(mainFont);

    return tLoaded;
}


void close(GameTextures & one)
{
    bgTexture.free();
    shipTexture.free();
    shipLivesTexture.free();

    bulletTexture.free();
    MonsterbulletTexture.free();

    monsterTypeA.free();
    monsterTypeB.free();
    monsterTypeC.free();

    crashTest.free();
    gameOver.free();
    youWin.free();

    one.pTexLBB.free();
    one.pTexLBT.free();
    one.pTexLCEB.free();
    one.pTexLCET.free();
    one.pTexLCOB.free();
    one.pTexLCOT.free();
    one.pTexRBB.free();
    one.pTexRBT.free();
    one.pTexRCEB.free();
    one.pTexRCET.free();
    one.pTexRCOB.free();
    one.pTexRCOT.free();

    textTexture.free();


    SDL_DestroyRenderer(mainRenderer);
    SDL_DestroyWindow(mainWindow);

    mainRenderer = NULL;
    mainWindow = NULL;
    mainFont = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}



