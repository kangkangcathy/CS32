#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

 void Peach::bonk()
 {
     if(Invincible)
     {
         return;
     }
     loseblood(1);
     noShootPower();
     noJumpPower();
     if(getWorld()->getPeach()->HP() > 0)
     {
         getWorld()->playSound(SOUND_PLAYER_HURT);
     }
     else
     {
         getWorld()->getPeach()->setDead();
     }
 }

void Peach::setJump()
{
    if(JumpPower)
    {
        remaining_jump_distance = 12;
    }
    else
    {
        remaining_jump_distance = 8;
    }
}
void Peach::doSomething()
{
    //if the peach is dead, end!
    if (!checkAlive())
        return;
    //check if she is currently invincible (Star Power)
    if(Invincible!=0)
    {
        //how to decrement the game ticks?
        setInvincible();
        InvincibleT --;
    }
    else
    {
        setnotInvincible();
    }
    
    
    //if the peach has shoot power
    if(ShootPower)
    {
        //if the time_to_recharge_before_next_fire is greater than zero, cannot shoot
        if(time_to_recharge_before_next_fire > 0)
        {
            time_to_recharge_before_next_fire --;
            noCanShoot();
        }
        //if the time_to_recharge_before_next_fire is zero, can shoot
        else if(time_to_recharge_before_next_fire == 0)
        {
            setCanShoot();
        }
    }
    
    //Peach must check to see if she currently overlaps with any other game object
    if(getWorld()->checkoverlap(getX(), getY()))
    {
        getWorld()->callbonk(getX(), getY(), getDirection());
    }
    
    //If Peach had previously initiated a jump and her remaining_jump_distance is > 0
    if(remaining_jump_distance>0)
    {
        //check to see if there is an object that blocks movement at destination position
        bool notstuck3 = getWorld()->hasnoblock(getX(), getY() + 4, KEY_PRESS_UP);
        if(notstuck3) //no block preventing it from moving upward 4 pixels
        {
            //jump
            moveTo(getX(), getY()+4);
            animate();
            remaining_jump_distance --;
            return;
        }
        else //block preventing it from moving upward 4 pixels
        {
            getWorld() ->callbonk(getX(), getY() + 4, KEY_PRESS_UP);
            remaining_jump_distance = 0;
            return;
        }
    }
    //if Peach was not actively jumping during the current tick,
    //then she must check to see if she is falling
    
    else
    {
        if( (getWorld()->hasnoblock(getX(), getY()-4, KEY_PRESS_DOWN)))
        {
            moveTo(getX(), getY()-4);
            animate();
        }
    }
    
    //getkey from keyboard to move peach
    int direction;
    //to perform movements of peach!
    if (getWorld()->getKey(direction))
    {
        switch (direction)
        {
                //if it wants to go left
            case KEY_PRESS_LEFT:
            {
                bool notstuck1 = true;
                setDirection(180);
                notstuck1 = getWorld()->hasnoblock(getX() - 4, getY(), direction);
                if (notstuck1)
                {
                    moveTo(getX() - 4, getY());
                    animate();
                    return;
                }
                else
                {
                    getWorld() ->callbonk(getX() - 4, getY(), direction);
                    return;
                }
                
                break;
            }
                //if it wants to go right
            case (KEY_PRESS_RIGHT):
            {
                bool notstuck2 = true;
                setDirection(0);
                notstuck2 = getWorld()->hasnoblock(getX() + 4, getY(), direction);
                if (notstuck2)
                {
                    moveTo(getX() + 4, getY());
                    animate();
                    return;
                }
                else
                {
                    getWorld() ->callbonk(getX() + 4, getY(), direction);
                    return;
                }
                
                break;
            }
                //if it wants to go up
            case (KEY_PRESS_UP):
            {
                bool notstuck3 = true;
                //check whether there is a block below it
                notstuck3 = getWorld()->hasnoblock(getX(), getY()-SPRITE_HEIGHT, direction); // 1 pixel below.. is getY()-SPRITE_HEIGHT ok?
                if(notstuck3) //no block beneath her, then do nothing
                {
                    return;
                }
                else //there is block beneath her and support her jump
                {
                    setJump();
                    //play the sound of jumping
                    getWorld() ->playSound(SOUND_PLAYER_JUMP);
                    return;
                }
                break;
            }
                //if it wants to go down
            case (KEY_PRESS_DOWN):
            {
                break;
            }
            case (KEY_PRESS_SPACE):
            {
                //getWorld()->addstuff(getWorld(), "PeachFire", getDirection(), getX(), getY());
                if(checkShootPower())
                {
                    getWorld()->addstuff(getWorld(), "PeachFire", getDirection(), getX(), getY());
                }
                break;
            }
        }
    }
}

void Buff::refreshPeach()
{
    if(getWorld()->hasnoblock(getX(), getY()-2, KEY_PRESS_DOWN))
    {
        moveTo(getX(),getY()-2);
    }
    int angle = getDirection();
    if(angle == 0) //if now it is facing to the right
    {
        bool move = getWorld() -> hasnoblock(getX()+2, getY(), KEY_PRESS_RIGHT);
        if(move)
        {
            moveTo(getX()+2,getY());
            return;
        }
        setDirection(180);
        return;
    }
    else if(angle == 180)  //if now it is facing to the left
    {
        bool move2 = getWorld() -> hasnoblock(getX()-2, getY(), KEY_PRESS_LEFT);
        if(move2)
        {
            moveTo(getX()-2,getY());
            return;
        }
        setDirection(0);
        return;
    }
}

void Buff::refreshbad()
{
    if(getWorld()->hasnoblock(getX(), getY()-2, KEY_PRESS_DOWN))
    {
        moveTo(getX(),getY()-2);
        return;
    }
    int angle = getDirection();
    if(angle == 0) //if now it is facing to the right
    {
        bool move = getWorld() -> hasnoblock(getX()+2, getY(), KEY_PRESS_RIGHT);
        if(!move)
        {
            setDead();
            return;
        }
        moveTo(getX()+2,getY());
        return;
        
    }
    else if(angle == 180)  //if now it is facing to the left
    {
        bool move2 = getWorld() -> hasnoblock(getX()-2, getY(), KEY_PRESS_LEFT);
        if(!move2)
        {
            setDead();
            return;
        }
        moveTo(getX()-2,getY());
        return;
    }
}

void Creature::badmove()
{
    //int direction = getDirection();
    /*
    //face to the right
    if(direction == 0 && getWorld()->hasnoblock(getX()+1, getY(), KEY_PRESS_RIGHT))
    {
        setDirection(180);
    }
    //face to the left
    else if (direction == 180 && getWorld()->hasnoblock(getX()-1, getY(), KEY_PRESS_LEFT))
    {
        setDirection(0);
    }
    //face to the right and no blocks below
    int seconddir = getDirection();
    if(seconddir == 0 && getWorld()->hasnoblock(getX(), getY()-4, KEY_PRESS_DOWN))
    {
        setDirection(180);
    }
    //face to the left and no blocks below
    else if(seconddir == 180 && getWorld()->hasnoblock(getX(), getY()-4, KEY_PRESS_DOWN))
    {
        setDirection(0);
    }
     */
    int nowdirection = getDirection();
    if(nowdirection == 0) //face to the right
    {
        if(!getWorld()->hasnoblock(getX()+1, getY(), KEY_PRESS_RIGHT))
        {
            setDirection(180);
            return;
        }
        else if(getWorld()->hasnoblock(getX()+8, getY()-4, KEY_PRESS_DOWN))
        {
            setDirection(180);
            return;
        }
        moveTo(getX()+1, getY());
        animate();
        return;
    }
    else if(nowdirection == 180)  //face to the left
    {
        if(!getWorld()->hasnoblock(getX()-1, getY(), KEY_PRESS_LEFT))
        {
            setDirection(0);
            return;
        }
        else if(getWorld()->hasnoblock(getX()-8, getY()-4, KEY_PRESS_DOWN))
        {
            setDirection(0);
            return;
        }
        moveTo(getX()-1, getY());
        animate();
        return;
    }
}
    
void Flower::doSomething()
{
    //check if it is overlaping with peach
    if(getWorld()->isPeach(getX(), getY()))
    {
        //It will increase the player’s score by 50 points
        getWorld()->increaseScore(50);
        //It will inform the Peach object that it now has the Shoot Power
        getWorld()->getPeach()->setShootPower();
        //It will set Peach’s hit points to 2
        getWorld()->getPeach()->setblood2();
        //It will immediately set its state to not-alive
        setDead();
        //It will play a sound of SOUND_PLAYER_POWERUP using GameWorld’s playSound() method
        getWorld() ->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    refreshPeach();
    return;
}

void Mushroom::doSomething()
{
    //check if it is overlaping with peach
    if(getWorld()->isPeach(getX(), getY()))
    {
        //It will increase the player’s score by 75 points
        getWorld()->increaseScore(75);
        //It will inform the Peach object that it now has the Jump Power
        getWorld()->getPeach()->setJumpPower();
        //It will set Peach’s hit points to 2
        getWorld()->getPeach()->setblood2();
        //It will immediately set its state to not-alive
        setDead();
        //It will play a sound of SOUND_PLAYER_POWERUP using GameWorld’s playSound() method
        getWorld() ->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    refreshPeach();
    return;
}

void Star::doSomething()
{
    //check if it is overlaping with peach
    if(getWorld()->isPeach(getX(), getY()))
    {
        //It will increase the player’s score by 100 points
        getWorld()->increaseScore(100);
        //It will inform the Peach object that it now has the Star Power for 150 game ticks.
        getWorld()->getPeach()->setStarPower(150);
        //It will immediately set its state to not-alive
        setDead();
        //It will play a sound of SOUND_PLAYER_POWERUP using GameWorld’s playSound() method
        getWorld() ->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    refreshPeach();
    return;
}

void PiranhaFireball::doSomething()
{
    //check if it is overlaping with peach
    if(getWorld()->isPeach(getX(), getY()))
    {
        getWorld()->getPeach()->damage();
        setDead();
        return;
    }
    refreshbad();
    return;
}

void PeachFireball::doSomething()
{
    if(getWorld()->canbeDamage(getX(),getY()))
    {
        //It will inform the object that it has been damaged
        getWorld()->DamageActor(getX(), getY());
        //It will immediately set its own state to not-alive
        setDead();
        return;
    }
    else
    {
        refreshbad();
    }
    return;
}

void Shell::doSomething()
{
    if(getWorld()->canbeDamage(getX(),getY()))
    {
        //It will inform the object that it has been damaged
        getWorld()->DamageActor(getX(), getY());
        //It will immediately set its own state to not-alive
        setDead();
        return;
    }
    refreshbad();
    return;
}

void Goomba::doSomething()
{
    if(!checkAlive())
    {
        return;
    }
    if(getWorld()->isPeach(getX(), getY()))
    {
        getWorld()->getPeach()->bonk();
        return;
    }
    badmove();
    return;
}

void Goomba::bonk()
{
    if(!getWorld()->isPeach((getX()), getY()))
    {
        return;
    }
    if(getWorld()->getPeach()->checkInvincible())
    {
        getWorld()->playSound(SOUND_PLAYER_KICK);
        {
            getWorld()->increaseScore(100);
            setDead();
        }
    }
}

void Goomba::damage()
{
    getWorld()->increaseScore(100);
    setDead();
}

void Koopa::doSomething()
{
    if(!checkAlive())
    {
        return;
    }
    if(getWorld()->isPeach(getX(), getY()))
    {
        getWorld()->getPeach()->bonk();
        setDead();
        getWorld()->addstuff(getWorld(), "shell", getDirection(), getX(), getY());
        return;
    }
    badmove();
    return;
}

void Koopa::bonk()
{
    if(!getWorld()->isPeach((getX()), getY()))
    {
        return;
    }
    if(getWorld()->getPeach()->checkInvincible())
    {
        getWorld()->playSound(SOUND_PLAYER_KICK);
        {
            getWorld()->increaseScore(100);
            setDead();
            getWorld()->addstuff(getWorld(), "shell", getDirection(), getX(), getY());
        }
    }
}

void Koopa::damage()
{
    getWorld()->increaseScore(100);
    setDead();
    getWorld()->addstuff(getWorld(), "shell", getDirection(), getX(), getY());
}

void Piranha::doSomething()
{
    if(!checkAlive())
    {
        return;
    }
    increaseAnimationNumber();
    if(getWorld()->isPeach(getX(), getY()))
    {
        getWorld()->getPeach()->bonk();
        return;
    }
    //The Piranha will then determine if Peach’s y coordinate is within
    //1.5*SPRITE_HEIGHT of Piranha’s y coordinate
    int piy = getY();
    if((getWorld()->getPeach()->getY()-piy<= 1.5*SPRITE_HEIGHT && getWorld()->getPeach()->getY()-piy>=0 )||(piy - getWorld()->getPeach()->getY()<= 1.5*SPRITE_HEIGHT && piy - getWorld()->getPeach()->getY()>=0))
    {
        int peachx = getWorld()->getPeach()-> getX();
        int pix = getX();
        if(peachx > pix)
        {
            setDirection(0);
        }
        else
        {
            setDirection(180);
        }
    }
    else
    {
        return;
    }
    //Piranha will check if it has a firing delay
    if(fireDelay>0)
    {
        decreaseFire();
        return;
    }
    //If there is no firing delay, then Piranha may choose to fire:
        int pix = getX();
        int piy2 = getY();
        int dir = getDirection();
        if((getWorld()->getPeach()->getX()-pix >=0 && getWorld()->getPeach()->getX()-pix < 8*SPRITE_WIDTH
           )||(pix - getWorld()->getPeach()->getX() >= 0 && pix - getWorld()->getPeach()->getX() < 8*SPRITE_WIDTH))
        {
            getWorld()->addstuff(getWorld(), "PiranhaFireball", dir, pix, piy2);
            getWorld()->playSound(SOUND_PIRANHA_FIRE);
            setFiredelay(40);
        }
}

void Piranha::bonk()
{
    if(!getWorld()->isPeach((getX()), getY()))
    {
        return;
    }
    if(getWorld()->getPeach()->checkInvincible())
    {
        getWorld()->playSound(SOUND_PLAYER_KICK);
        {
            getWorld()->increaseScore(100);
            setDead();
        }
    }
}

void Piranha::damage()
{
    getWorld()->increaseScore(100);
    setDead();
    getWorld()->addstuff(getWorld(), "shell", getDirection(), getX(), getY());
}

void Block::bonk()
{
    bool goodie = checkNoGoodie();
    if(goodie)
    {
        getWorld()->playSound(SOUND_PLAYER_BONK);
    }
    else if(goodie == false && checkRelease() == false)
    {
        getWorld()->playSound(SOUND_POWERUP_APPEARS);
        if(returngoodie() == 1)
        {
            getWorld()->addstuff(getWorld(), "StarGoodie", 0, getX(), getY()+8);
        }
        else if(returngoodie() == 2)
        {
            getWorld()->addstuff(getWorld(), "FlowerGoodie", 0, getX(), getY()+8);
        }
        else if(returngoodie() == 3)
        {
            getWorld()->addstuff(getWorld(), "MushroomGoodie", 0, getX(), getY()+8);
        }
        releaseGoodie();
    }
    else
    {
        getWorld()->playSound(SOUND_PLAYER_BONK);
    }
    
}

int Block::returngoodie()
{
    if(HoldStarGoodie)
    {
        return 1;
    }
    if(HoldFlowerGoodie)
    {
        return 2;
    }
    if(HoldMushroomGoodie)
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

bool Block::checkNoGoodie()
{
    if(!HoldGoodie)
    {
        return true;
    }
    return false;
}

void Block::releaseGoodie()
{
    setrelease();
    setfalseholdgooie();
    //and then how to make the goodie appear?
    //Introduce a goodie object of the appropriate type (Flower, Star or Mushroom) exactly 8 pixels above the block that was bonked (the same x coordinate as the block, but y+8 from the block)
    
}

void Pipe::bonk()
{
    getWorld()->playSound(SOUND_PLAYER_BONK);
}
void Flag::doSomething()
{
    if(!checkAlive())
    {
        return;
    }
    else
    {
        //if peach is overlapping with flag
        if(getWorld()->isPeach(getX(), getY()))
        {
            //increase player's score by 1000
            getWorld()->increaseScore(1000);
            setDead();
            //It will inform the StudentWorld object that the current level was completed (so the StudentWorld can advance to the next level)
            getWorld()->setlevelcomplete();
        }
    }
}

void Mario::doSomething()
{
    if(!checkAlive())
    {
        return;
    }
    else
    {
        //if peach is overlapping with flag
        if(getWorld()->isPeach(getX(), getY()))
        {
            //increase player's score by 1000
            getWorld()->increaseScore(1000);
            setDead();
            //It will inform the StudentWorld object that the player has won the game
            getWorld()->setwonthegame();
        }
    }
}
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
