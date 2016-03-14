class pbullet
{
public:

    pbullet(int, int);

    int pbulletvelocity = -12;
    void ptravel();
    void ptravelDown();
    void prenderbullet();
    void pdestroy();
    void psetCollider();
    vector<SDL_Rect>& pgetCollider();
private:

    int pbPosX, pbPosY;
    int pbVelY;
    vector<SDL_Rect> pbCollider;

};

void pcreateBullet(vector<pbullet> &, int, int);
void prenderBullet(vector<pbullet> &currentBullet, int);

void psetColliders(vector<pbullet> &);
void pfindCollision(vector<pbullet>& , mainShip);
void pfindCColision(vector<pbullet>& , shipProtector&, GameTextures&);
bool pkillBulletAtEnd(vector<SDL_Rect> &);


