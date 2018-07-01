/*
 * Name: Corey Dixon
 * Moveable Class Definition
 * Project Bullet Hell
 * Date: 4/29/2013
 * Description: Moveable class, derived from GameObject, adds velocity and
 *				the move function. tick now also calls move. checkCollision
 *				now checks where the object will be next rather than where
 *				it is now.
 */

#pragma once
#include "GameObject.h"
class Moveable :
	public GameObject
{
public:
	// constructors
	Moveable(void);
	Moveable(double _x, double _y, int _width, int _height, int _type);
	Moveable(double _x, double _y, double _z, double _rotationRate, int _width, int _height, int _type);
	// destructor
	~Moveable(void);
	//accessors
	double getVeloX() const;
	double getVeloY() const;
	//mutators
	void setVeloX(const double &_x);
	void setVeloY(const double &_y);
	//misc
	virtual void move(const double &deltaTime);
	void tick(const double &deltaTime);
	bool checkCollision(GameObject *other, const double &deltaTime);
protected:
	double velocityX, velocityY;
	double lastX, lastY;
	double oldVelocityX, oldVelocityY;

};

