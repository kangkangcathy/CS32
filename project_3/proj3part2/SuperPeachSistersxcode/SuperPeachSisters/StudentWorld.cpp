#include "StudentWorld.h"
#include "Level.h"
#include "Actor.h"
#include "GameConstants.h"
#include <string>
#include <vector>
#include <iostream> // defines the overloads of the << operator
#include <sstream>  // defines the type std::ostringstream
#include <iomanip>  // defines the manipulator setw
using namespace std;

GameWorld *createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), tick(0), levelcomplete(false), wongame(false)
{
    m_peach = nullptr;
}
StudentWorld::~StudentWorld()
{
    cleanUp();
}

bool StudentWorld::checkoverlap(int x, int y)
{
    for (int i = 0; i < vi.size(); i++)
    {
        int corx = vi[i]->getX();
        int cory = vi[i]->getY();
        if (corx == x & cory == y)
        {
            return true;
        }
    }
    return false;
}

void StudentWorld::callbonk(int x, int y, int dir)
{
    switch (dir)
    {
        case KEY_PRESS_RIGHT:
        {
            for (int i = 0; i < vi.size(); i++)
            {
                int corx = vi[i]->getX();
                int cory = vi[i]->getY();
                if ((corx >= x && corx <= x + SPRITE_WIDTH -1 )&&  ((cory + SPRITE_HEIGHT - 1 >= y && cory <= y)|| (y + SPRITE_HEIGHT - 1 >= cory && y <= cory)))
                {
                    vi[i]->bonk();
                }
                
            }
            break;
        }
        case KEY_PRESS_LEFT:
        {
            for (int i = 0; i < vi.size(); i++)
            {
                int corx = vi[i]->getX();
                int cory = vi[i]->getY();
                if ((corx <= x && corx + SPRITE_WIDTH-1 >= x) && ((cory + SPRITE_HEIGHT - 1 >= y && cory <= y)|| (y + SPRITE_HEIGHT - 1 >= cory && y <= cory)))
                {
                    vi[i]->bonk();
                }
                
            }
            break;
        }
        case KEY_PRESS_UP:
        {
            for (int i = 0; i < vi.size(); i++)
            {
                
                int corx = vi[i]->getX();
                int cory = vi[i]->getY();
                if (((corx + SPRITE_WIDTH -1 >= x && corx <= x)||(x + SPRITE_WIDTH -1 >= corx && x <= corx) )
                    && (cory>=y && y +SPRITE_HEIGHT-1>=cory) )
                {
                    vi[i]->bonk();
                }
                
            }
            break;
        }
    }
}
bool StudentWorld::hasnoblock(int x, int y, int dir)
{
    switch (dir)
    {
        case KEY_PRESS_RIGHT:
        {
            for (int i = 0; i < vi.size(); i++)
            {
                //check if the object itself can block others
                if(vi[i] -> checkPrevent())
                {
                    int corx = vi[i]->getX();
                    int cory = vi[i]->getY();
                    if ((corx >= x && corx <= x + SPRITE_WIDTH -1 )&&  ((cory + SPRITE_HEIGHT - 1 >= y && cory <= y)|| (y + SPRITE_HEIGHT - 1 >= cory && y <= cory)))
                    {
                        //vi[i]->bonk();
                        return false;
                    }
                }
            }
            break;
        }
        case KEY_PRESS_LEFT:
        {
            for (int i = 0; i < vi.size(); i++)
            {
                if(vi[i] -> checkPrevent())
                {
                    int corx = vi[i]->getX();
                    int cory = vi[i]->getY();
                    if ((corx <= x && corx + SPRITE_WIDTH-1 >= x) && ((cory + SPRITE_HEIGHT - 1 >= y && cory <= y)|| (y + SPRITE_HEIGHT - 1 >= cory && y <= cory)))
                    {
                        //vi[i]->bonk();
                        return false;
                    }
                }
            }
            break;
        }
        case KEY_PRESS_UP:
        {
            for(int i = 0; i < vi.size(); i ++)
            {
                if(vi[i] -> checkPrevent())
                {
                    int corx = vi[i]->getX();
                    int cory = vi[i]->getY();
                    if(((corx + SPRITE_WIDTH -1 >= x && corx <= x)||(x + SPRITE_WIDTH -1 >= corx && x <= corx) )
                       && (cory>=y && y +SPRITE_HEIGHT-1>=cory) )
                    {
                        return false;
                    }
                }
            }
            break;
        }
        case KEY_PRESS_DOWN:
        {
            for(int i = 0; i < vi.size(); i ++)
            {
                if(vi[i] -> checkPrevent())
                {
                    int corx = vi[i]->getX();
                    int cory = vi[i]->getY();
                    if(((corx + SPRITE_WIDTH -1 >= x && corx <= x)||(x + SPRITE_WIDTH -1 >= corx && x <= corx) ) && (cory<=y && cory+SPRITE_HEIGHT-1 >=y))
                    {
                        return false;
                    }
                }
            }
            break;
        }
        default: //help to check whether there is a goodie overlaping with the block
        {
            for(int i = 0; i < vi.size(); i ++)
            {
                if(!vi[i] -> checkPrevent())
                {
                    int corx = vi[i]->getX();
                    int cory = vi[i]->getY();
                    if(corx == x && cory == y)
                    {
                        return false;
                    }
                }
            }
            break;
        }
    }
    return true;
}



int StudentWorld::init()
{
    int numLevel = getLevel();
    ostringstream level;
    level.fill('0');
    level << "level" << setw(2) << numLevel << ".txt";
    Level lev(assetPath());
    string level_file = level.str();
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
    {
        cerr <<"Could not find "<< level_file <<" data file"<< endl;
        //cerr << "Could not find level01.txt data file" << endl;
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_fail_bad_format)
    {
        cerr << level_file << " is improperly formatted" << endl;
        //cerr << "level01.txt is improperly formatted" << endl;
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_success)
    {
        for (int i = 0; i < GRID_WIDTH; i++)
        {
            for (int j = 0; j < GRID_HEIGHT; j++)
            {
                Level::GridEntry ge;
                ge = lev.getContentsOf(i, j);
                switch (ge)
                {
                    case Level::peach:
                        m_peach = new Peach(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT);
                        break;
                    case Level::block:
                        vi.push_back(new Block(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 0));
                        break;
                    case Level::pipe:
                        vi.push_back(new Pipe(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                        break;
                    case Level::flag:
                        vi.push_back(new Flag(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                        break;
                    case Level::mario:
                        vi.push_back(new Mario(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                        break;
                    case Level::flower_goodie_block:
                        vi.push_back(new Block(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT, 2));
                        //vi.push_back(new Flower(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                        break;
                    case Level::mushroom_goodie_block:
                        vi.push_back(new Block(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT,3));
                        //vi.push_back(new Mushroom(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                        break;
                    case Level::star_goodie_block:
                        vi.push_back(new Block(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT,1));
                        //vi.push_back(new Star(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                        break;
                        //piranha's fire ball and peach fire ball haven't been set up
                        //shell haven't been set up
                    case Level::goomba:
                        vi.push_back(new Goomba(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                        break;
                    case Level::koopa:
                        vi.push_back(new Koopa(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                        break;
                    case Level::piranha:
                        vi.push_back(new Piranha(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
                        break;
                    default:
                        break;
                }
            }
        }
        return GWSTATUS_CONTINUE_GAME;
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::addstuff(StudentWorld* sw, string name, int dir, int x, int y)
{
    int item = 0;
    if(name == "PiranhaFireball")
    {
        item = 1;
    }
    if(name == "FlowerGoodie")
    {
        item = 2;
    }
    if(name == "MushroomGoodie")
    {
        item = 3;
    }
    if(name == "StarGoodie")
    {
        item = 4;
    }
    if(name == "shell")
    {
        item = 5;
    }
    if(name == "PeachFire")
    {
        item = 6;
    }
    switch(item)
    {
        case 1:
            vi.push_back(new PiranhaFireball(sw, dir, x, y));
            break;
        case 2:
            vi.push_back(new Flower(sw, x, y));
            break;
        case 3:
            vi.push_back(new Mushroom(sw, x, y));
            break;
        case 4:
            vi.push_back(new Star(sw, x, y));
            break;
        case 5:
            vi.push_back(new Shell(sw, dir, x, y));
            break;
        case 6:
            vi.push_back(new PeachFireball(sw, dir, x, y));
            break;
    }
}

int StudentWorld::move()
{
    tick++;
    if (!m_peach->checkAlive())
    {
        
        return GWSTATUS_PLAYER_DIED;
    }
    vector<Actor*>::iterator a = vi.begin();
    for(a = vi.begin(); a != vi.end();)
    {
        if(!(*a)->checkAlive())
        {
            delete *a;
            a = vi.erase(a);
        }
        else
        {
            (*a)->doSomething();
            a++;
        }
    }
    m_peach->doSomething();
    stringstream os;
    os << "Lives: " <<getLives() <<" Level: " << getLevel() << " Points: " << getScore();
    if(m_peach -> checkStarPower()) os << " StarPower!";
    if(m_peach -> checkShootPower()) os << " ShootPower!";
    if(m_peach -> checkJumpPower()) os << " JumpPower!";
    std::string b = os.str();
    setGameStatText(b);
    if(checklevelcomplete())
    {
        return GWSTATUS_FINISHED_LEVEL;
    }
    if(checkwonthegame())
    {
        return GWSTATUS_PLAYER_WON;
    }
    return GWSTATUS_CONTINUE_GAME;
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //    decLives();
}

bool StudentWorld::isPeach(int x, int y)
{
    int disx = m_peach->getX()-x;
    int disy = m_peach->getY()-y;
    if(-3<=disx && disx<=3 && disy>=-3 && disy<=3)
    {
        return true;
    }
    return false;
}

bool StudentWorld::canbeDamage(int x, int y)
{
    for (int i = 0; i < vi.size(); i++)
    {
        
        int corx = vi[i]->getX();
        int cory = vi[i]->getY();
        bool result = vi[i]->checkDamagable();
        int disx = corx-x;
        int disy = cory-y;
        if (-3<=disx && 3>=disx && -3<=disy && 3>=disy && result && checkActorAlive(corx, cory))
        {
            return true;
        }
    }
    return false;
}

void StudentWorld::DamageActor(int x, int y)
{
    for (int i = 0; i < vi.size(); i++)
    {
        
        int corx = vi[i]->getX();
        int cory = vi[i]->getY();
        bool result = vi[i]->checkDamagable();
        int disx = corx-x;
        int disy = cory-y;
        if (-3<=disx && 3>=disx && -3<=disy && 3>=disy && result && vi[i]->checkAlive())
        {
            vi[i]->damage();
        }
    }
}

bool StudentWorld::checkActorAlive(int x, int y)
{
    for (int i = 0; i < vi.size(); i++)
    {
        
        int corx = vi[i]->getX();
        int cory = vi[i]->getY();
        if (corx == x && cory == y)
        {
            return vi[i]->checkAlive();
        }
    }
    return false;
}

void StudentWorld::cleanUp()
{
    delete m_peach;
    vector<Actor*>::iterator a = vi.begin();
    for(a = vi.begin(); a != vi.end();)
    {
        delete *a;
        a = vi.erase(a);
    }
}

