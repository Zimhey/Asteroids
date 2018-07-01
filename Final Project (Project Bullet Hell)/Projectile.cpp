/*
 * Name: Corey Dixon
 * Projectile Member Function Definitions
 * Project Bullet Hell
 * Date: 3/16/2013
 * Description: adds damage data member. collides with asteroids
 */

#include "Projectile.h"
#include <math.h>

// constructors
Projectile::Projectile(void) :
	Moveable()
{
	damage = 0;
}

Projectile::Projectile(double _x, double _y, int _width, int _height, int _type) :
	Moveable(_x, _y, _width, _height, _type)
{
	damage = 34;
}

Projectile::Projectile(double _x, double _y, double _z, double _rotationRate, int _width, int _height, int _type) :
	Moveable(_x, _y, _z, _rotationRate, _width, _height, _type)
{
	damage = 34;
}

Projectile::Projectile(double _x, double _y) :
	Moveable(_x, _y, -10, 0, 24, 24, error)
{
	velocityX = velocityY = 0;
}

Projectile::Projectile(double _x, double _y, double destX, double destY) :
	Moveable(_x, _y, -10, 0, 24, 24, error)
{

	damage = 34;

	double speed = 1000;
	double angle = atan2(destY - y, destX - x);
	angle *= (180/ PI);
	velocityX = cos( angle * PI / 180) * speed;
	velocityY = sin( angle * PI / 180) * speed;
}

// destructor
Projectile::~Projectile(void)
{
}

// accessors
int Projectile::getDamage() const
{
	return damage;
}

// mutators
void Projectile::setDamage(const int &_damage)
{
	damage = _damage;
}

// misc
void Projectile::tick(const double &deltaTime)
{
	Moveable::tick(deltaTime);
}

void Projectile::collide(GameObject *other)
{
	if(other == 0)	// NULL
	{
		velocityX = 0;
		velocityY = 0;
		return;
	}
	if(other->getType() == asteroid1)
	{
		die();
	}
}