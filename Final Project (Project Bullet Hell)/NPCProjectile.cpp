/*
 * Name: Corey Dixon
 * NPCProjectile Member Function Definitions
 * Project Bullet Hell
 * Date: 5/15/2013
 * Description: derived from Projectile, doesn't change much other than it now
 *				uses the enemy_projectile texture.
 */

#include "NPCProjectile.h"
#include <cmath>

// constructors
NPCProjectile::NPCProjectile(double _x, double _y) :
	Projectile(_x, _y, -5, 540, 24, 24, enemy_projectile)
{
	velocityX = velocityY = 0;
}

NPCProjectile::NPCProjectile(double _x, double _y, double destX, double destY) :
	Projectile(_x, _y, -5, 540, 24, 24, enemy_projectile)
{
	double speed = 1000;
	double angle = atan2(destY - y, destX - x);
	angle *= (180/ PI);
	velocityX = cos( angle * PI / 180) * speed;
	velocityY = sin( angle * PI / 180) * speed;	
}

NPCProjectile::NPCProjectile(double _x, double _y, double destX, double destY, int speed) :
	Projectile(_x, _y, -5, 540, 24, 24, enemy_projectile)
{
	double angle = atan2(destY - y, destX - x);
	angle *= (180/ PI);
	velocityX = cos( angle * PI / 180) * speed;
	velocityY = sin( angle * PI / 180) * speed;	
}

// destructor
NPCProjectile::~NPCProjectile(void)
{
}

void NPCProjectile::collide(GameObject *other)
{
	if(other == 0)	// NULL
	{
		velocityX = 0;
		velocityY = 0;
		return;
	}
	if(other->getType() == asteroid1)
		die();
	if(other->getType() == ship)
		die();
	if(other->getType() == projectile)
		die();
}