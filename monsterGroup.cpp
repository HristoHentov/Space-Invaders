monsterGroup::monsterGroup()
{
    head = NULL;
}

void monsterGroup::createElement(node * &head, int x, int y, int t)
{

    if(!head)
    {
        timesGone++;
        head = new node;
        head -> currentMonster = new monster;
        head -> renderFLAG = false;
        head -> nodeIndex = timesGone;
        head -> currentMonster -> create(x, y, t);
        head -> next = NULL;
        return;
    }

    createElement(head -> next, x, y, t);
}

void monsterGroup::renderMGroup(node * head)
{

    if(!head)
        return;


    if(head -> renderFLAG == false)
    {
        head -> currentMonster->renderMonster(2);
    }



    renderMGroup(head -> next);

}

void monsterGroup::clearElement(node * &head, node * previousEl, node * nextEl)
{
    if(!head)
        return;
}

void monsterGroup::spawn(node * &head)
{
    int x = 200;
    int y = 50;
    int t = 1;
    int next = -1;

    for (int i = 0; i < 55; i++)
    {


        if(i % 11 == 0)
        {
            y += 50;
            next++;
            x = 200;
        }


        switch(next)
        {

        case 0:
        {
            t = 1;
            break;
        }
        case 1:
        {
            t = 2;
            break;
        }
        case 2:
        {
            t = 2;
            break;
        }
        case 3:
        {
            t = 3;
            break;
        }
        case 4:
        {
            t = 3;
            break;
        }

        default:
        {
            t = 3;
            break;
        }

        }

        createElement(head, x, y, t);


        x += 80;

    }
}

void monsterGroup::moveMGroup(node * &head, bool track, bool changeDirection)
{
    if(!head)
        return;
    head -> currentMonster -> moveMonster(changeDirection, track);

}

void monsterGroup::setDirection(node * &head)
{
    if(!head)
        return;

if(head -> moveFLAG == true)
{



    head -> currentMonster -> setSize();

    if(head -> currentMonster -> getX() < 0) // REACHED LEFT END OF SCR
    {
        cout << "\nreached end of scrn!";
        cout << "X IS : " << head -> currentMonster -> getX();
        changeDirection = false; // means it will keep going left
        track = true; //
    }


    if(((head -> currentMonster -> getX()) + (head -> currentMonster -> getWidth())) > gameWidth)//REACHED RIGHT END OF SCR
    {
        changeDirection = true;
        track = true;
    }

}

    setDirection(head -> next);

    moveMGroup(head, track, changeDirection);

}

bool monsterGroup::getHeading(node * head)
{
    return track;
}


void monsterGroup::setGColliders(node * head)
{
    if(!head)
        return;
    head -> currentMonster -> setCollider();

    setGColliders(head -> next);
}


void monsterGroup::checkAndDestroy(int nodeNumber, node * &head)
{
    if(!head)
        return;
    if(head -> nodeIndex == nodeNumber)
    {
        head -> currentMonster -> deleteCollider();
    }

    checkAndDestroy(nodeNumber, head -> next);
}



void monsterGroup::shoot(node * head, int chosenNPC)
{
    if(!head)
        return;
    if(head -> nodeIndex == chosenNPC)
        head -> currentMonster -> mShoot();

    shoot(head -> next, chosenNPC);
}

