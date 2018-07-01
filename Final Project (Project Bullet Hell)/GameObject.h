/*
 * Name: Corey Dixon
 * GameObject Class Definition
 * Project Bullet Hell
 * Date: 4/13/2013
 * Description: Base class for all Objects, has a ton of data members.
 *				location (x, y, z), rotation (theta) rotation rate,
 *				width and height, type which is used to tell what the
 *				object is, its type is also which texture will be used
 *				when drawing, collidable is for collision, if collidable
 *				objects can collide, alive is used to determine if an object
 *				is dead and should be removed from the game. Has misc functions
 *				such as draw which draws the object, drawDebug which draws
 *				debug lines around the object so you can visually see where
 *				the objects bounds are for collision. has virtual functions
 *				such as checkCollision, collide and tick.
 *				tick rotates the object around, however changes in derived classes.
 *				checkCollision determines if two objects are touching eachother
 *				collide does nothing in this class, however derived classes will
 *				have different behavior depending on what it collides into.
 */

#pragma once
#include "GameConstants.h"

class GameObject
{
public:
	// constructors
	GameObject(void);
	GameObject(double _x, double _y, int _width, int _height, int _type);
	GameObject(double _x, double _y, double _z, double _rotationRate, int _width, int _height, int _type);
	// destructor
	virtual ~GameObject(void);
	// accessors
	double getX() const;
	double getY() const;
	double getZ() const;
	int getWidth() const;
	int getHeight() const;
	double getTheta() const;
	int getType() const;
	bool isCollidable() const;
	bool isAlive() const;
	// mutators
	void setX(const double &_x);
	void setY(const double &_y);
	void setZ(const double &_z);
	void setWidth(const int &_width);
	void setHeight(const int &_height);
	void setTheta(const double &_theta);
	void setCollidable(const bool &_collidable);

	// misc
	void draw();
	void drawDebug();
	virtual bool checkCollision(GameObject *other, const double &deltaTime);
	virtual void collide(GameObject *other);
	virtual void tick(const double &deltaTime);
	virtual void die();


protected:
	bool collidable, alive;
	double x, y, z, theta, rotationRate;
	int width, height, type;
};