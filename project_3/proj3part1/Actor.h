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
          : GraphObject(ID, x, y, dir, depth, size), m_world(sw), alive(true)
      {
      }

      virtual void doSomething() = 0;

      bool checkAlive() const { return alive; }
      void setDead() { alive = false; }
      StudentWorld *getWorld() const { return m_world; }
      virtual ~Actor() {} // do it later

private:
      StudentWorld *m_world;
      bool alive;
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
      // virtual void bonk();
      virtual void doSomething() {}
      virtual ~Creature() {}

private:
      int health;
};

class Peach : public Creature
{
public:
      Peach(StudentWorld *sw, int x, int y)
          : Creature(sw, IID_PEACH, x, y, 0, 0, 1.0, 1), StarPower(false),
            JumpPower(false), FirePower(false), Invincible(false)
      {
      }
      virtual void doSomething();
      virtual void bonk();
      virtual ~Peach() {}

private:
      bool StarPower;
      bool JumpPower;
      bool FirePower;
      bool Invincible;
};

//Block Section
class Goomba : public Creature
{
public:
      Goomba(StudentWorld *sw, int ID, int x, int y, int dir, int depth, float size, int blood)
          : Creature(sw, IID_GOOMBA, x, y, pow(-1, rand() % 100) * 90 + 90, 0, 1.0, 1)
      {
      }
      virtual void doSomething();
      virtual ~Goomba() {}

private:
      //bool HoldGoodie;
};

class Koopa : public Creature
{
public:
      Koopa(StudentWorld *sw, int ID, int x, int y, int dir, int depth, float size, int blood)
          : Creature(sw, IID_KOOPA, x, y, pow(-1, rand() % 100) * 90 + 90, 0, 1.0, 1)
      {
      }
      virtual void doSomething();
      virtual ~Koopa() {}

private:
};

class Piranha : public Creature
{
public:
      Piranha(StudentWorld *sw, int ID, int x, int y, int dir, int depth, float size, int blood)
          : Creature(sw, IID_PIRANHA, x, y, pow(-1, rand() % 100) * 90 + 90, 0, 1.0, 1), fireDelay(0)
      {
      }
      virtual void doSomething();
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
      virtual void doSomething() {}
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
      virtual ~Mario() {}

private:
};

class Building : public Actor
{
public:
      Building(StudentWorld *sw, int ID, int x, int y, int dir, int depth, float size)
          : Actor(sw, ID, x, y, dir, depth, size)
      {
      }
      virtual void doSomething() {}
      virtual void bonk() = 0;
      virtual ~Building() {}

private:
};

class Block : public Building
{
public:
      Block(StudentWorld *sw, int x, int y)
          : Building(sw, IID_BLOCK, x, y, 0, 2, 1.0)
      {
      }
      virtual void doSomething() {}
      virtual void bonk() {}
      virtual ~Block() {}

private:
};

class Pipe : public Building
{
public:
      Pipe(StudentWorld *sw, int x, int y)
          : Building(sw, IID_PIPE, x, y, 0, 2, 1.0)
      {
      }
      virtual void doSomething();
      void bonk();
      virtual ~Pipe() {}

private:
};

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
