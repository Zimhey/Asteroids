/*
 * Name: Corey Dixon
 * NPC Member Function Definitions
 * Project Bullet Hell
 * Date: 4/29/2013
 * Description: for enemy ships. WIP (not implemented yet) currently just creates
 *				an object with the enemy_ship texture
 */

#include "NPC.h"

// constructor
NPC::NPC(double _x, double _y)
{
	x = _x;
	y = _y;
	z = 0;
	theta = 0;
	rotationRate = 0;
	height = width = 64;
	type = enemy_ship;
	collidable = true;
	alive = true;
	velocityX = velocityY = 0;
	health = 100;
}

// destructor
NPC::~NPC(void)
{
}

// not implemented yet. will probably add to tick function
void NPC::ai()
{

}

void NPC::collide(GameObject *other)
{
	if(other->getType() == projectile)
		health -= 34;		// change this to use projectile damage (requires cast)
	if(other->getType() == asteroid1)
		health -= 50;	// use mass to compute dmg (width * height) / something)
}