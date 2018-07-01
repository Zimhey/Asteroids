/*
 * Name: Corey Dixon
 * Projectile Class Definition
 * Project Bullet Hell
 * Date: 3/16/2013
 * Description: adds damage data member. collides with asteroids
 */

#pragma once
#include "Moveable.h"
class Projectile :
	public Moveable
{
public:
	// constructor
	Projectile(void);
	Projectile(double _x, double _y, int _width, int _height, int _type);
	Projectile(double _x, double _y, double _z, double _rotationRate, int _width, int _height, int _type);
	Projectile(double _x, double _y);	// stays in same place
	Projectile(double _x, double _y, double destX, double destY);	// moves towards location given in destX, destY
	// destructor
	~Projectile(void);
	// accessor
	int getDamage() const;
	// mutator
	void setDamage(const int &_damage);
	// misc
	void tick(const double &deltaTime);
	void collide(GameObject *other);

private:
	int damage;
};

