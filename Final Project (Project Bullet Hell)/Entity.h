/*
 * Name: Corey Dixon
 * Entity Class Definition
 * Project Bullet Hell
 * Date: 4/6/2013
 * Description: Entity class, derived from Moveable, which is derived from GameObject
				Adds health data member
 */

#pragma once
#include "Moveable.h"
class Entity :
	public Moveable
{
public:
	// constructor
	Entity(void);
	Entity(double _x, double _y, int _width, int _height, int _type);
	Entity(double _x, double _y, double _z, double _rotationRate, int _width, int _height, int _type);
	// destructor
	~Entity(void);
	// accessor
	double getHealth() const;
	// mutator
	void setHealth(const double &_health);
	// misc
	void tick(const double &deltaTime);
protected:
	double health;
};

