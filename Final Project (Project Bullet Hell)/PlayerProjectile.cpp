/*
 * Name: Corey Dixon
 * PlayerProjectile Member Function Definitions
 * Project Bullet Hell
 * Date: 5/15/2013
 * Description: derived from Projectile class, changes nothing but the texture(type).
 */

#include "PlayerProjectile.h"
#include <cmath>

// constructors
PlayerProjectile::PlayerProjectile(double _x, double _y) :
	Projectile(_x, _y, -5, 720, 24, 24, projectile)
{
	velocityX = velocityY = 0;
}

PlayerProjectile::PlayerProjectile(double _x, double _y, double destX, double destY) :
	Projectile(_x, _y, -5, 720, 24, 24, projectile)
{
	double speed = 1000;
	double angle = atan2(destY - y, destX - x);
	angle *= (180/ PI);
	velocityX = cos( angle * PI / 180) * speed;
	velocityY = sin( angle * PI / 180) * speed;	
}

PlayerProjectile::PlayerProjectile(double _x, double _y, double destX, double destY, int speed) :
	Projectile(_x, _y, -5, 720, 24, 24, projectile)
{
	double angle = atan2(destY - y, destX - x);
	angle *= (180/ PI);
	velocityX = cos( angle * PI / 180) * speed;
	velocityY = sin( angle * PI / 180) * speed;	
}

// destructor
PlayerProjectile::~PlayerProjectile(void)
{
}

void PlayerProjectile::collide(GameObject *other)
{
	if(other == 0)	// NULL
	{
		velocityX = 0;
		velocityY = 0;
		return;
	}
	if(other->getType() == asteroid1)
		die();
	if(other->getType() == enemy_ship)
		die();
	if(other->getType() == enemy_projectile)
		die();
}