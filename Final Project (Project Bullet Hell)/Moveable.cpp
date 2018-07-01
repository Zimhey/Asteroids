/*
 * Name: Corey Dixon
 * Moveable Member Function Definitions
 * Project Bullet Hell
 * Date: 4/29/2013
 * Description: Moveable class, derived from GameObject, adds velocity and
 *				the move function. tick now also calls move. checkCollision
 *				now checks where the object will be next rather than where
 *				it is now.
 */

#include "Moveable.h"
#include <cmath>

// constructors
Moveable::Moveable(void) :
	GameObject()
{
	velocityX = velocityY = 0;
	oldVelocityX = oldVelocityY = 0;
	lastX = lastY = 0;
}

Moveable::Moveable(double _x, double _y, int _width, int _height, int _type) :
	GameObject(_x, _y, _width, _height, _type)
{
	velocityX = velocityY = 0;
	oldVelocityX = oldVelocityY = 0;
	lastX = lastY = 0;
}

Moveable::Moveable(double _x, double _y, double _z, double _rotationRate, int _width, int _height, int _type) :
	GameObject(_x, _y, _z, _rotationRate, _width, _height, _type)
{
	velocityX = velocityY = 0;
	oldVelocityX = oldVelocityY = 0;
	lastX = lastY = 0;
}

// destructor
Moveable::~Moveable(void)
{
}

// accessor
double Moveable::getVeloX() const
{
	return velocityX;
}

double Moveable::getVeloY() const
{
	return velocityY;
}

// mutator
void Moveable::setVeloX(const double &_x)
{
	x = _x;
}

void Moveable::setVeloY(const double &_y)
{
	y = _y;
}

// misc
void Moveable::tick(const double &deltaTime)
{
	GameObject::tick(deltaTime);	// rotates object
	move(deltaTime);
}

void Moveable::move(const double &deltaTime)
{
	x += velocityX * deltaTime;
	y += velocityY * deltaTime;
}

bool Moveable::checkCollision(GameObject *other, const double &deltaTime)
{
	Moveable *obj =  &static_cast<Moveable&>(*other);

	double w = 0.5 * (width + other->getWidth());
	double h = 0.5 * (height + other->getHeight());
	double dx = x + (velocityX * deltaTime) - other->getX() + (obj->getVeloX() * deltaTime);
	double dy = y + (velocityY * deltaTime) - other->getY() + (obj->getVeloY() * deltaTime);

	return (abs(dx) <= w && abs(dy) <= h);
}
