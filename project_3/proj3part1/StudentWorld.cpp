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
    : GameWorld(assetPath), tick(0)
{
    m_peach = nullptr;
}
StudentWorld::~StudentWorld()
{
    cleanUp();
}

bool StudentWorld::hasblock(int x, int y, int dir)
{
    switch (dir)
    {
    case KEY_PRESS_RIGHT:
    {
        for (int i = 0; i < vi.size(); i++)
        {
            int corx = vi[i]->getX();
            int cory = vi[i]->getY();
            if (corx >= x && corx <= x + SPRITE_WIDTH -1 && cory == y)
            {
                return false;
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
            if (corx <= x && corx + SPRITE_WIDTH-1 >= x && cory == y)
            {
                return false;
            }
        }
        break;
    }
    }
    /*
    case up:
    {
        for (int i = 0; i < vi.size(); i++)
        {
            int corx = vi[i].getX();
            int cory = vi[i].getY();
            if (cory <= y && cory + 4 >= y && corx == x) //here may need to change the 4 later depoend on speed varies with time
            {
                return false;
            }
        }
    }
    case down:
    {
        for (int i = 0; i < vi.size(); i++)
        {
            int corx = vi[i].getX();
            int cory = vi[i].getY();
            if (cory + SPRITE_HEIGHT >= y && cory + SPRITE_HEIGHT - 4 <= y && corx == x)
            {
                return false;
            }
        }
    }
    */
    return true;
}

int StudentWorld::init()
{
    int numLevel = getLevel();
    ostringstream level;
    level.fill('0');
    level << "level" << setw(2) << numLevel << ".txt";
    Level lev(assetPath());
    string level_file = "level01.txt";
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
    {
        cerr << "Could not find level01.txt data file" << endl;
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_fail_bad_format)
    {
        cerr
            << "level01.txt is improperly formatted" << endl;
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
                    vi.push_back(new Block(this, i * SPRITE_WIDTH, j * SPRITE_HEIGHT));
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

int StudentWorld::move()
{
    tick++;
    for (int i = 0; i < vi.size(); i++)
    {
        if (vi[i]->checkAlive())
        {
            vi[i]->doSomething();
            if (!m_peach->checkAlive())
            {
                return GWSTATUS_PLAYER_DIED;
            }
        }
    }
    m_peach->doSomething();
    return GWSTATUS_CONTINUE_GAME;
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
//    decLives();
//    return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
    delete m_peach;
    m_peach = nullptr;
    vi.erase(vi.begin(), vi.end());
}
