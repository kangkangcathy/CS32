#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include "Level.h"
#include <string>
#include <vector>
#include <list>

class Actor;
class Peach;
class Twinkler;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    Peach *getPeach() const { return m_peach; }
    virtual void addstuff(StudentWorld* sw, std::string name, int dir, int x, int y);
    bool hasnoblock(int x, int y, int dir);
    void callbonk(int x, int y, int dir);
    bool checkoverlap(int x, int y);
    bool isPeach(int x, int y);
    bool canbeDamage(int x, int y);
    bool checklevelcomplete(){return levelcomplete;}
    virtual void setlevelcomplete() {levelcomplete = true;}
    virtual void setwonthegame(){wongame = true;}
    bool checkwonthegame(){return wongame;}
    virtual void DamageActor(int x, int y);
    bool checkActorAlive(int x, int y);
    virtual void cleanUp();
    
private:
    std::vector<Actor *> vi;
    int tick;
    bool levelcomplete;
    bool wongame;
    Peach *m_peach;
};

#endif // STUDENTWORLD_H_
