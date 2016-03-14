class GameTexture
{
public:

    GameTexture();
    ~GameTexture();

    bool loadFromFile(string);
    void deallocate();
    void render(int, int);
    void free();
    int getWidth();
    int getHeight();
    bool loadFromRenderedText(string textureText, SDL_Color textColor);

private:

    SDL_Texture * mTexture;
    int tWidth;
    int tHeight;
};
