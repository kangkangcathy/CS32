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
  bool hasblock(int x, int y, int dir);
  virtual void cleanUp();

private:
  std::vector<Actor *> vi;
  int tick;
  Peach *m_peach;
};

#endif // STUDENTWORLD_H_
