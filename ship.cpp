mainShip::mainShip()
{
    sPosX = 640;
    sPosY = 675;
    sVelX = 0;
    sVelY = 0;

    shipColliders.resize(3);

    shipColliders[0].x = 0;
    shipColliders[0].y = 0;
    shipColliders[0].w = 0;
    shipColliders[0].h = 0;

    shipColliders[1].x = 0;
    shipColliders[1].y = 0;
    shipColliders[1].w = 0;
    shipColliders[1].h = 0;

    shipColliders[2].x = 0;
    shipColliders[2].y = 0;
    shipColliders[2].w = 0;
    shipColliders[2].h = 0;
}

void mainShip::handleEvent(SDL_Event &event)
{
    if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {

        case SDLK_LEFT:
        {
            sVelX -= shipVelocity;
            break;
        }
        case SDLK_RIGHT:
        {
            sVelX += shipVelocity;
            break;
        }
        case SDLK_SPACE:
        {
            createBullet(bulletContainer, sPosX, sPosY - 12);
            rendercheck = true;
            break;
        }

        }
    }

    else if(event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
        {
            sVelX += shipVelocity;
            break;
        }
        case SDLK_RIGHT:
        {
            sVelX -= shipVelocity;
            break;
        }
        case SDLK_SPACE:
        {
            break;
        }
        }
    }

}


void mainShip::moveShip()
{
    sPosX += sVelX;
    if ((sPosX < 0) || (sPosX + shipWidth > gameWidth))
    {
        sPosX -= sVelX;

    }

}

void mainShip::render()
{
    shipTexture.render(sPosX,sPosY);
}

void mainShip::setShipColliders()
{
    shipColliders[0].x = sPosX;
    shipColliders[0].y = sPosY + 12;
    shipColliders[0].w = 20;
    shipColliders[0].h = 15;

    shipColliders[1].x = sPosX + shipColliders[0].w;
    shipColliders[1].y = sPosY;
    shipColliders[1].w = 25;
    shipColliders[1].h = 29;

    shipColliders[2].x = sPosX + shipColliders[0].w + shipColliders[1].w;
    shipColliders[2].y = sPosY + 12;
    shipColliders[2].w = 20;
    shipColliders[2].h = 15;
}

vector<SDL_Rect> &mainShip::getColliders()
{
    return shipColliders;
}

void mainShip::renderColliders()
{
    SDL_RenderDrawRect(mainRenderer, &shipColliders[0]);
    SDL_RenderDrawRect(mainRenderer, &shipColliders[1]);
    SDL_RenderDrawRect(mainRenderer, &shipColliders[2]);

}


