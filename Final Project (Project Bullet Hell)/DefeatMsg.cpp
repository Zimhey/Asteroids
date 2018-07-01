/*
 * Name: Corey Dixon
 * DeafMsg Member Function Definitions
 * Project Bullet Hell
 * Date: 5/16/2013
 * Description: Used to display "You have been defeated" on the screen for a certain amount of time
 */

#include "DefeatMsg.h"

// constructor
DefeatMsg::DefeatMsg()
{
	x = 1280/2;
	y = 720/4;
	z = 0;
	alive = true;
	collidable = false;
	theta = 0;
	rotationRate = 0;
	type = defeat;
	lifeTime = 0;
	width = (int)(936 * 0.8);
	height = (int)(124 * 0.8);
}

// destructor
DefeatMsg::~DefeatMsg(void)
{
}

// misc
void DefeatMsg::tick(const double &deltaTime)
{
	lifeTime += deltaTime;
	if(lifeTime > 1.25)	// die after alive for 1.25 seconds
		die();
}