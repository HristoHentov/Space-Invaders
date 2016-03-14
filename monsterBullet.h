class monsterBullet
{
public:

    bullet(int, int);

    static const int bulletvelocity = 12;
    void travelDown();
    void renderbullet();
    void destroy();
    void setCollider();
    vector<SDL_Rect>& getCollider();
private:

    int bPosX, bPosY;
    int bVelY;
    vector<SDL_Rect> bCollider;

};

void createBullet(vector<bullet> &, int, int);
void createMonsterBullet(vector<mBullet> &, int, int);
void renderBullet(vector<bullet> &currentBullet, int);

void setColliders(vector<bullet> &);
void findCollision(vector<bullet>& , shipProtector&, monsterGroup&, GameTextures&);
bool killBulletAtEnd(vector<SDL_Rect> &);


