bullet::bullet(int posX, int posY)
{
    bPosX = posX;
    bPosY = posY;
    bVelY = 0;
    bCollider.resize(1);
    bCollider[0].w = 4;
    bCollider[0].h = 16;
}

void bullet::travel()
{
    bPosY -= bulletvelocity;

}

void bullet::travelDown()
{
    bPosY += bulletvelocity;
}

void bullet::renderbullet()
{
    bulletTexture.render(bPosX, bPosY);
}

void bullet::setCollider()
{
    bCollider[0].x = bPosX;
    bCollider[0].y = bPosY;
}

vector<SDL_Rect> &bullet::getCollider()
{
    return bCollider;
}


bool killBulletAtEnd(vector<SDL_Rect>& a)
{
    int top,bottom;

    for (int Cbox = 0; Cbox < a.size(); Cbox ++)
    {
        top = a[Cbox].y;
        bottom = a[Cbox].y + a[Cbox].h;
    }


    if((bottom >= 736) || (top <= -16))
        return true;
    else
        return false;
}

void createBullet(vector<bullet> &currentBullet, int PosX, int PosY)
{

    bullet theBullet(PosX + 31 , PosY);

    currentBullet.push_back(theBullet);

}

void renderBullet(vector<bullet> &currentBullet, int side)
{
    if(side == 0)
    {
        unsigned int last = currentBullet.size();
        for(int i = 0; i < last; i++)
        {
            currentBullet[i].renderbullet();
            currentBullet[i].travel();
        }

        return;
    }

    else
    {
        unsigned int last = currentBullet.size();
        for(int i = 0; i < last; i++)
        {
            currentBullet[i].renderbullet();
            currentBullet[i].travelDown();
        }
    }

}




void setColliders(vector<bullet> &currentBullet)
{
    for (int i = 0; i < currentBullet.size(); i++)
        currentBullet[i].setCollider();
}
