class monster
{

public:
    monster();

    void create(int, int, int);
    void renderMonster(int);
    void mShoot();
    void moveMonster(bool, bool);
    void kill();
    vector<SDL_Rect> &getCollider();
    void setCollider();
    void setSize();
    int getX();
    int getY();
    int getWidth();
    int displayCollider();
    void clearCollider();
    void deleteCollider();
    void renderCollider();

private:

    int spawnX, spawnY;
    int monsterType;
    int offsetX, offsetY;
    vector<SDL_Rect> mCollider;
    int monsterWidth;
    int monsterHeight;
    bool changeDir;

};
