GameTexture::GameTexture()
{
    mTexture = NULL;
    tWidth = 0;
    tHeight = 0;
}

GameTexture::~GameTexture()
{
    free();
}

bool GameTexture::loadFromFile(string path)
{
    free(); // Clear previous texture.
    SDL_Texture * newTexture = NULL;
    SDL_Surface * loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface)
        cout << "\nFailed to load image at " << path << " ERROR: " << SDL_GetError();
    else
    {
        newTexture = SDL_CreateTextureFromSurface(mainRenderer, loadedSurface);
        if(!newTexture)
            cout << "\nUnable to create game texture form file. EROR: " << SDL_GetError();
        else
        {
            tWidth = loadedSurface -> w;
            tHeight = loadedSurface -> h;
        }

        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;

}

bool GameTexture::loadFromRenderedText(string textureText, SDL_Color textColor)
{
    free();

    SDL_Surface * textSurface = TTF_RenderText_Solid(mainFont, textureText.c_str(), textColor);
    if(!textSurface)
        cout << "Failed to render text surface! TTF Error: " << SDL_GetError();
    else
    {
        mTexture = SDL_CreateTextureFromSurface(mainRenderer, textSurface);
        if(!mTexture)
            cout << "Failed to create texture from text! Render error: " << SDL_GetError();
        else
        {
            tWidth = textSurface -> w;
            tHeight = textSurface -> h;
        }

        SDL_FreeSurface(textSurface);
    }

    return mTexture != NULL;
}

void GameTexture::free()
{
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        tWidth = 0;
        tHeight = 0;
    }
}

void GameTexture::render(int x, int y)
{
    SDL_Rect renderquad = {x, y, tWidth, tHeight};
    SDL_RenderCopy(mainRenderer, mTexture, NULL, &renderquad);
}

int GameTexture::getWidth()
{
    return tWidth;
}

int GameTexture::getHeight()
{
    return tHeight;
}
