/*
 * Name: Corey Dixon
 * DeafMsg Class Definition
 * Project Bullet Hell
 * Date: 5/16/2013
 * Description: Used to display "You have been defeated" on the screen for a certain amount of time
 */

#pragma once
#include "GameObject.h"
class DefeatMsg :
	public GameObject
{
public:
	// constructor
	DefeatMsg(void);
	// destructor
	~DefeatMsg(void);
	// misc
	void tick(const double &deltaTime);
protected:
	double lifeTime;
};

