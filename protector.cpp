shipProtector::shipProtector(int x, int y)
{
    pPosX = x;
    pPosY = y;

    pColliders.resize(12); // creates 12 colliders
    pColliders[0].w = 32;
    pColliders[0].h = 28;

    pColliders[1].w = 32;
    pColliders[1].h = 28;

    pColliders[2].w = 32;
    pColliders[2].h = 25;

    pColliders[3].w = 32;
    pColliders[3].h = 25;

    pColliders[4].w = 46;
    pColliders[4].h = 32;

    pColliders[5].w = 46;
    pColliders[5].h = 32;

    pColliders[6].w = 43;
    pColliders[6].h = 25;

    pColliders[7].w = 43;
    pColliders[7].h = 25;

    pColliders[8].w = 19;
    pColliders[8].h = 25;

    pColliders[9].w = 19;
    pColliders[9].h = 25;

    pColliders[10].w = 19;
    pColliders[10].h = 17;

    pColliders[11].w = 19;
    pColliders[11].h = 17;
}


void shipProtector::setColliders()
{

    pColliders[0].x = pPosX;
    pColliders[0].y = pPosY + protectorHeight - (pColliders[0].h / 2);

    pColliders[1].x = pPosX +  protectorWidth  - (pColliders[1].w);
    pColliders[1].y = pPosY +  protectorHeight - (pColliders[1].h);

    pColliders[2].x = pPosX;
    pColliders[2].y = pPosY + protectorHeight - (pColliders[1].h) - (pColliders[2].h);

    pColliders[3].x = pPosX +  protectorWidth  - (pColliders[3].w);
    pColliders[3].y = pPosY +  protectorHeight - pColliders[1].h - (pColliders[3].h);

    pColliders[4].x = pPosX;
    pColliders[4].y = pPosY + (pColliders[6].h);

    pColliders[5].x = pPosX +  protectorWidth  - (pColliders[5].w);
    pColliders[5].y = pPosY + (pColliders[7].h);

    pColliders[6].x = pPosX;
    pColliders[6].y = pPosY;

    pColliders[7].x = pPosX + protectorWidth - (pColliders[7].w) - 3;
    pColliders[7].y = pPosY;

    pColliders[8].x = pPosX + (pColliders[6].w) + 3;
    pColliders[8].y = pPosY;

    pColliders[9].x = pPosX + protectorWidth / 2;
    pColliders[9].y = pPosY;

    pColliders[10].x = pPosX + (pColliders[4].w);
    pColliders[10].y = pPosY + (pColliders[8].h);

    pColliders[11].x = pPosX + protectorWidth / 2;
    pColliders[11].y = pPosY + (pColliders[8].h);

}

void shipProtector::renderProtector(int protectorID, int targetToKill, GameTextures& two)
{

    two.pTexLBB.render(pPosX, pPosY);
    two.pTexRBB.render(pPosX, pPosY);
    two.pTexLBT.render(pPosX, pPosY);
    two.pTexLCEB.render(pPosX, pPosY);
    two.pTexLCET.render(pPosX, pPosY);
    two.pTexLCOB.render(pPosX, pPosY);
    two.pTexLCOT.render(pPosX, pPosY);
    two.pTexRBT.render(pPosX, pPosY);
    two.pTexRCEB.render(pPosX, pPosY);
    two.pTexRCET.render(pPosX, pPosY);
    two.pTexRCOB.render(pPosX, pPosY);
    two.pTexRCOT.render(pPosX, pPosY);

}

int shipProtector::getX()
{
    return pPosX;
}

int shipProtector::getY()
{
    return pPosY;
}


vector<SDL_Rect> &shipProtector::getColliders(int current)
{
    return pColliders;
}

void shipProtector::coutCollision()
{

}

void shipProtector::destroyProtectorEl(int target, GameTextures & currentPT)
{
    if(target > -1)
    {
        pColliders[target].w = 0;
        pColliders[target].h = 0;
        pColliders[target].x = 0;
        pColliders[target].y = 0;
    }

    switch(target)
    {
    case 0:
    {
        currentPT.pTexLBB.~GameTexture();
        break;
    }
    case 1:
    {
        currentPT.pTexRBB.~GameTexture();
        break;
    }
    case 2:
    {
        currentPT.pTexLBT.~GameTexture();
        break;
    }
    case 3:
    {
        currentPT.pTexRBT.~GameTexture();
        break;
    }
    case 4:
    {
        currentPT.pTexLCOB.~GameTexture();
        break;
    }
    case 5:
    {
        currentPT.pTexRCOB.~GameTexture();
        break;
    }
    case 6:
    {
        currentPT.pTexLCOT.~GameTexture();
        break;
    }
    case 7:
    {
        currentPT.pTexRCOT.~GameTexture();
        break;
    }
    case 8:
    {
        currentPT.pTexLCET.~GameTexture();
        break;
    }
    case 9:
    {
        currentPT.pTexRCET.~GameTexture();
        break;
    }
    case 10:
    {
        currentPT.pTexLCEB.~GameTexture();
        break;
    }
    case 11:
    {
        currentPT.pTexRCEB.~GameTexture();
        break;
    }
    }


}

void shipProtector::getColliderPosX(int target)
{
    cout << "\nCOLLIDER2 " << target << " has X pos of : " <<  pColliders[target].x;
}

void shipProtector::getColliderPosY(int target)
{
    cout << "\nCOLLIDER2 " << target << " has Y pos of : " <<  pColliders[target].y;
}
