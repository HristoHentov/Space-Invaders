class mainShip
{

public:

    mainShip();

    static const int shipWidth = 64;
    static const int shipHeight = 64;
    static const int shipVelocity = 10;

    void handleEvent(SDL_Event &event);
    void moveShip();
    void render();
    void setShipColliders();
    vector<SDL_Rect> &getColliders();
    void renderColliders();

private:
    vector <SDL_Rect> shipColliders;
    int sPosX, sPosY;
    int sVelX, sVelY;


};
