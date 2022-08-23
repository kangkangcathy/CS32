#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

void Peach::bonk()
{
    getWorld()->playSound(SOUND_PLAYER_BONK);
}
void Peach::doSomething()
{
      //if the player is dead, end!
      if (!checkAlive())
            return;
      int direction;
      //check if the player has met a block wall
      if (getWorld()->getKey(direction))
      {
            switch (direction)
            {
            case KEY_PRESS_LEFT:
            {
                  bool notstuck1 = true;
                  setDirection(180);
                  notstuck1 = getWorld()->hasblock(getX() - 4, getY(), direction);
                  if (notstuck1)
                  {
                        moveTo(getX() - 4, getY());
                        animate();
                  }
                  else
                  {
                      bonk();
                        return;
                  }

                  break;
            }
            case (KEY_PRESS_RIGHT):
            {
                  bool notstuck2 = true;
                  setDirection(0);
                  notstuck2 = getWorld()->hasblock(getX() + 4, getY(), direction);
                  if (notstuck2)
                  {
                        moveTo(getX() + 4, getY());
                        animate();
                  }
                  else
                  {
                      bonk();
                        return;
                  }

                  break;
            }
            case (KEY_PRESS_UP):
            {
                  break;
            }
            case (KEY_PRESS_DOWN):
            {
                  break;
            }
            }
      }
}
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
