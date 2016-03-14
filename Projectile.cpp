pbullet::pbullet(int posX, int posY)
{
    pbPosX = posX;
    pbPosY = posY;
    pbVelY = 0;
    pbCollider.resize(1);
    pbCollider[0].w = 4;
    pbCollider[0].h = 16;
}

void pbullet::ptravel()
{
    pbPosY -= pbulletvelocity;

}

void pbullet::ptravelDown()
{
    pbPosY += pbulletvelocity;
}

void pbullet::prenderbullet()
{
    MonsterbulletTexture.render(pbPosX, pbPosY);
}

void pbullet::psetCollider()
{
    pbCollider[0].x = pbPosX;
    pbCollider[0].y = pbPosY;
}

vector<SDL_Rect> &pbullet::pgetCollider()
{
    return pbCollider;
}


bool pkillBulletAtEnd(vector<SDL_Rect>& a)
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

void pcreateBullet(vector<pbullet> &pcurrentBullet, int pPosX, int pPosY)
{

    pbullet ptheBullet(pPosX + 31 , pPosY);

    pcurrentBullet.push_back(ptheBullet);

}

void prenderBullet(vector<pbullet> &pcurrentBullet, int pside)
{
    if(pside == 0)
    {
        unsigned int last = pcurrentBullet.size();
        for(int i = 0; i < last; i++)
        {
            pcurrentBullet[i].prenderbullet();
            pcurrentBullet[i].ptravel();
        }

        return;
    }
}




void psetColliders(vector<pbullet> &pcurrentBullet)
{
    for (int i = 0; i < pcurrentBullet.size(); i++)
        pcurrentBullet[i].psetCollider();
}

