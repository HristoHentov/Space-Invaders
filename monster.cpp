monster::monster()
{
    spawnX = -50;
    spawnY = -50;
    offsetX = 14;
    offsetY = 18;
    mCollider.resize(1);
    mCollider[0].w = 0;
    mCollider[0].h = 32;
    mCollider[0].x = -1;
    mCollider[0].y = -1;
    monsterWidth = 0;
    monsterHeight = 32;
    monsterType = 1;
    changeDir = false;

}

void monster::create(int x, int y, int type)
{

    spawnX = x;
    spawnY = y;
    monsterType = type;
}

void monster::renderMonster(int check)
{
    if (check > 1)
    {
        switch(monsterType)
        {
        case 1:
        {
            monsterTypeA.render(spawnX, spawnY);
            break;
        }
        case 2:
        {
            monsterTypeB.render(spawnX, spawnY);
            break;
        }
        case 3:
        {
            monsterTypeC.render(spawnX, spawnY);
            break;
        }

        default:
        {
            break;
        }
        }
    }
    else
    {
        crashTest.render(spawnX, spawnY);
    }

}

void monster::mShoot()
{
    pcreateBullet(pbulletContainer, spawnX, spawnY -12);
}

void monster::moveMonster(bool changeDir, bool result)
{
    if(!changeDir)
        spawnX += offsetX;

    else if(changeDir)
        spawnX -= offsetX;

    if(result)
        spawnY += offsetY;


}
void monster::setCollider()
{
    mCollider.resize(1);

    mCollider[0].x = spawnX;
    mCollider[0].y = spawnY;

    switch(monsterType)
    {
    case 1:
    {
        mCollider[0].w = 32;
        break;
    }
    case 2:
    {
        mCollider[0].w = 44;
        break;
    }
    case 3:
    {
        mCollider[0].w = 48;
        break;
    }
    }
}

vector<SDL_Rect> &monster::getCollider()
{
    return mCollider;
}

void monster::setSize()
{
    switch(monsterType)
    {
    case 1:
    {
        monsterWidth = 32;
        break;
    }
    case 2:
    {
        monsterWidth = 44;
        break;
    }
    case 3:
    {
        monsterWidth = 48;
        break;
    }
    }
}

int monster::getX()
{
    return spawnX;
}

int monster::getY()
{
    return spawnY;
}
int monster::getWidth()
{
    return monsterWidth;
}

void monster::clearCollider()
{

    mCollider[0].x = -1250;
    mCollider[0].y = -1250;
    spawnX = -1250;
    spawnY = -1250;
}

int monster::displayCollider()
{
    return mCollider[0].x;
}

void monster::deleteCollider()
{
    mCollider.erase(mCollider.begin());
}

void monster::renderCollider()
{
    SDL_RenderDrawRect(mainRenderer, &mCollider[0]);
}
