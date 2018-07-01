/*
 * Name: Corey Dixon
 * Entity Class Definition
 * Project Bullet Hell
 * Date: 4/6/2013
 * Description: Entity class, derived from Moveable, which is derived from GameObject
				Adds health data member
 */

#include "Entity.h"

// constructors
Entity::Entity(void) :
	Moveable()
{
	health = 100;
}

Entity::Entity(double _x, double _y, int _width, int _height, int _type)  :
	Moveable(_x, _y, _width, _height, _type)
{
	health = 100;
}

Entity::Entity(double _x, double _y, double _z, double _rotationRate, int _width, int _height, int _type)	:
	Moveable(_x, _y, _z, _rotationRate, _width, _height, _type)
{
	health = 100;
}

// destructor
Entity::~Entity(void)
{
}

// accesors
double Entity::getHealth() const
{
	return health;
}

// mutators
void Entity::setHealth(const double &_health)
{
	health = _health;
}

// misc
void Entity::tick(const double &deltaTime)
{
	if(health < 0)	// object dead
	{
		die();
		return;
	}

	Moveable::tick(deltaTime);
}