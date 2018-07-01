/*
 * Name: Corey Dixon
 * Asteroid Class Definition
 * Project Bullet Hell
 * Date: 4/30/2013
 * Description: Asteroid class used by game to create asteroids
 *				that fly across the screen
 */

#pragma once
#include "Entity.h"
class Asteroid :
	public Entity
{
public:
	// constructors
	Asteroid(double _x, double _y);
	Asteroid(double _x, double _y, double destX, double destY);
	// destructor
	~Asteroid(void);
	// misc
	void move(const double &deltaTime);
	void tick(const double &deltaTime);
	void collide(GameObject *other);
protected:
	void undoMove();
};

