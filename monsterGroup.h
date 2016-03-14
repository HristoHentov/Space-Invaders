struct node
{
    monster * currentMonster;
    bool renderFLAG = true;
    bool moveFLAG = true;
    int nodeIndex;

    node * next;

};

class monsterGroup
{
public:
    monsterGroup();
    /** NEW FUNCTIONS **/

    void createElement(node * &, int, int, int);
    void renderMGroup(node *);
    void clearElement(node * &, node *, node *);
    void spawn(node *&);
    void moveMGroup(node * &, bool, bool);
    void setDirection(node *&);
    bool getHeading(node *);
    void setGColliders(node *);
    void killMonster(node * &head);
    void checkAndDestroy(int, node* &);
    void shoot(node *, int);


private:
    vector <monster> monsterSet;
    bool changeDirection = false;
    int tempSize;
    node * head;
};
