#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include "StudentWorld.h"
#include "GameWorld.h"
#include "GameController.h"

class StudentWorld;


//Actor secion
class Actor : public GraphObject
{
public:
    Actor(StudentWorld *sw, int ID, int x, int y, int dir, int depth, float size)
    : GraphObject(ID, x, y, dir, depth, size), m_world(sw), alive(true), prevent(false), damagable(false)
    {
    }
    
    virtual void doSomething() = 0;
    bool checkAlive() const { return alive; }
    void setPrevent() { prevent = true;}
    bool checkPrevent() const {return prevent;}
    void setDead() { alive = false; }
    StudentWorld *getWorld() const { return m_world; }
    virtual void bonk() = 0;
    bool checkDamagable() const {return damagable;}
    void setdamagable(){damagable = true;}
    virtual ~Actor() {} // do it later
    virtual void damage() = 0;
    
private:
    StudentWorld *m_world;
    bool alive;
    bool prevent;
    bool damagable;
};

//Creature Section
class Creature : public Actor
{
public:
    Creature(StudentWorld *sw, int ID, int x, int y, int dir, int depth, float size, int blood)
    : Actor(sw, ID, x, y, dir, depth, size), health(blood)
    {
    }
    virtual int blood() { return health; }
    virtual void loseblood(int num) { health -= num; }
    virtual void setblood2() {health = 2;}
    // virtual void bonk();
    virtual void badmove();
    int HP(){return health;}
    virtual ~Creature() {}
    
private:
    int health;
};

class Peach : public Creature
{
public:
    Peach(StudentWorld *sw, int x, int y)
    : Creature(sw, IID_PEACH, x, y, 0, 0, 1.0, 1), StarPower(0),
    JumpPower(false), ShootPower(false), Invincible(false), CanShoot(false),
    remaining_jump_distance(0), time_to_recharge_before_next_fire(0),InvincibleT(0)
    
    {
        setdamagable();
    }
    virtual void doSomething();
    virtual void setShootPower() {ShootPower = true;}
    virtual void noShootPower() {ShootPower = false;}
    bool checkShootPower() {return ShootPower;}
    virtual void setStarPower(int a) {StarPower = a;}
    virtual void noStarPower() {StarPower = 0;}
    bool checkStarPower() {return StarPower;}
    virtual void setJumpPower() {JumpPower = true;}
    virtual void noJumpPower() {JumpPower = false;}
    bool checkJumpPower() {return JumpPower;}
    virtual void setInvincible() {Invincible = true;}
    virtual void setInvincibleT(int a){InvincibleT = a;}
    virtual void setnotInvincible() {Invincible = false;}
    bool checkInvincible() {return Invincible;}
    virtual void setCanShoot() {CanShoot = true;}
    virtual void setJump();
    virtual void noCanShoot() {CanShoot = false;}
    virtual void bonk();
    virtual void damage(){bonk();}
    virtual ~Peach() {}
    
    
private:
    int StarPower;
    bool JumpPower;
    bool ShootPower;
    bool Invincible;
    int InvincibleT;
    bool CanShoot;
    int remaining_jump_distance;
    int time_to_recharge_before_next_fire;
};

//Block Section
class Goomba : public Creature
{
public:
    Goomba(StudentWorld *sw, int x, int y)
    : Creature(sw, IID_GOOMBA, x, y, pow(-1, rand() % 100) * 90 + 90, 0, 1.0, 1)
    {
        setdamagable();
    }
    virtual void doSomething();
    virtual void bonk();
    virtual void damage();
    virtual ~Goomba() {}
    
private:
};

class Koopa : public Creature
{
public:
    Koopa(StudentWorld *sw, int x, int y)
    : Creature(sw, IID_KOOPA, x, y, pow(-1, rand() % 100) * 90 + 90, 0, 1.0, 1)
    {
        setdamagable();
    }
    virtual void doSomething();
    virtual void bonk();
    virtual void damage();
    virtual ~Koopa() {}
    
private:
};

class Piranha : public Creature
{
public:
    Piranha(StudentWorld *sw, int x, int y)
    : Creature(sw, IID_PIRANHA, x, y, pow(-1, rand() % 100) * 90 + 90, 0, 1.0, 1), fireDelay(0)
    {
        setdamagable();
    }
    virtual void doSomething();
    virtual void decreaseFire(){fireDelay --;}
    virtual void setFiredelay(int i){fireDelay = i;}
    virtual void bonk();
    virtual void damage();
    virtual ~Piranha() {}
    
private:
    int fireDelay;
};

class Buff : public Actor
{
public:
    Buff(StudentWorld *sw, int ID, int x, int y, int dir, int depth, float size, bool peach, bool enemy)
    : Actor(sw, ID, x, y, dir, depth, size), isPeach(peach), isEnemy(enemy)
    {
    }
    virtual void doSomething(){}
    virtual void refreshPeach();
    virtual void refreshbad();
    virtual ~Buff() {}
    
private:
    bool isPeach;
    bool isEnemy;
};

class Flower : public Buff
{
public:
    Flower(StudentWorld *sw, int x, int y)
    : Buff(sw, IID_FLOWER, x, y, 0, 1, 1.0, false, false)
    {
    }
    virtual void doSomething();
    virtual void bonk(){}
    virtual void damage(){}
    virtual ~Flower() {}
    
private:
};

class Mushroom : public Buff
{
public:
    Mushroom(StudentWorld *sw, int x, int y)
    : Buff(sw, IID_MUSHROOM, x, y, 0, 1, 1.0, false, false)
    {
    }
    virtual void doSomething();
    virtual void bonk(){}
    virtual void damage(){}
    virtual ~Mushroom() {}
    
private:
};

class Star : public Buff
{
public:
    Star(StudentWorld *sw, int x, int y)
    : Buff(sw, IID_STAR, x, y, 0, 1, 1.0, false, false)
    {
    }
    virtual void doSomething();
    virtual void bonk(){}
    virtual void damage(){}
    virtual ~Star() {}
    
private:
};

class PiranhaFireball : public Buff
{
public:
    PiranhaFireball(StudentWorld *sw, int dir, int x, int y)
    : Buff(sw, IID_PIRANHA_FIRE, x, y, dir, 1, 1.0, false, false)
    {
    }
    virtual void doSomething();
    virtual void bonk(){}
    virtual void damage(){}
    virtual ~PiranhaFireball() {}
    
private:
};

class PeachFireball : public Buff
{
public:
    PeachFireball(StudentWorld *sw, int dir, int x, int y)
    : Buff(sw, IID_PEACH_FIRE, x, y, dir, 1, 1.0, false, false)
    {
    }
    virtual void doSomething();
    virtual void bonk(){}
    virtual void damage(){}
    virtual ~PeachFireball() {}
    
private:
};

class Shell : public Buff
{
public:
    Shell(StudentWorld *sw, int dir, int x, int y)
    : Buff(sw, IID_SHELL, x, y, dir, 1, 1.0, false, false)
    {
    }
    virtual void doSomething();
    virtual void bonk(){}
    virtual void damage(){}
    virtual ~Shell() {}
    
private:
};

class Flag : public Actor
{
public:
    Flag(StudentWorld *sw, int x, int y)
    : Actor(sw, IID_FLAG, x, y, 0, 1, 1.0)
    {
    }
    virtual void doSomething();
    virtual void bonk(){}
    virtual void damage(){}
    virtual ~Flag() {}
    
private:
};

class Mario : public Actor
{
public:
    Mario(StudentWorld *sw, int x, int y)
    : Actor(sw, IID_MARIO, x, y, 0, 1, 1.0)
    {
    }
    virtual void doSomething();
    virtual void bonk(){}
    virtual void damage(){}
    virtual ~Mario() {}
    
private:
};

class Building : public Actor
{
public:
    Building(StudentWorld *sw, int ID, int x, int y, int dir, int depth, float size)
    : Actor(sw, ID, x, y, dir, depth, size)
    {
        setPrevent();
    }
    virtual void doSomething() {}
    virtual ~Building() {}
    
private:
};

class Block : public Building
{
public:
    Block(StudentWorld *sw, int x, int y, int type)
    : Building(sw, IID_BLOCK, x, y, 0, 2, 1.0), HoldGoodie(false),HoldStarGoodie(false), HoldFlowerGoodie(false), HoldMushroomGoodie(false),HasReleased(false)
    {
        if(type == 0)
        {
            return;
        }
        if(type == 1)
        {
            HoldStarGoodie = true;
        }
        else if(type == 2)
        {
            HoldFlowerGoodie = true;
        }
        else if(type == 3)
        {
            HoldMushroomGoodie = true;
        }
        HoldGoodie = true;
    }
    virtual void doSomething() {}
    virtual void bonk();
    virtual void settrueholdgoodie(){ HoldGoodie = true;}
    virtual void setfalseholdgooie(){ HoldGoodie = false;}
    //set hold any goodies
    int returngoodie();
    virtual bool checkNoGoodie();
    virtual void releaseGoodie();
    virtual void setrelease(){ HasReleased = true;}
    virtual bool checkRelease(){return HasReleased;}
    virtual void damage(){}
    virtual ~Block() {}
private:
    bool HoldStarGoodie;
    bool HoldFlowerGoodie;
    bool HoldMushroomGoodie;
    bool HoldGoodie;
    bool HasReleased;
};

class Pipe : public Building
{
public:
    Pipe(StudentWorld *sw, int x, int y)
    : Building(sw, IID_PIPE, x, y, 0, 2, 1.0)
    {
        
    }
    virtual void doSomething() {}
    virtual void bonk();
    virtual void damage(){}
    virtual ~Pipe() {}
    
private:
};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
