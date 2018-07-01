/*
 * Name: Corey Dixon
 * GameObject Member Function Definitions
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

#include "GameObject.h"
#include <windows.h>
#include <windowsx.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <cmath>
#pragma comment(lib,"opengl32.lib")

// constructors
GameObject::GameObject(void)
{
	x = y = z = theta = rotationRate = 0;
	width = height = 128;
	type = error;
	collidable = alive = true;
}

GameObject::GameObject(double _x, double _y, int _width, int _height, int _type) :
	x	(_x),
	y	(_y),
	width	(_width),
	height	(_height),
	type	(_type)
{
	z = theta = rotationRate = 0;
	collidable = alive = true;

}

GameObject::GameObject(double _x, double _y, double _z, double _rotationRate, int _width, int _height, int _type) :
	x	(_x),
	y	(_y),
	z	(_z),
	rotationRate	(_rotationRate),
	width	(_width),
	height	(_height),
	type	(_type)
{
	theta = 0;
	collidable = alive = true;
}

// destructor
GameObject::~GameObject(void)
{
}

// accessors
double GameObject::getX() const
{
	return x;
}

double GameObject::getY() const
{
	return y;
}

double GameObject::getZ() const
{
	return z;
}

int GameObject::getWidth() const
{
	return width;
}

int GameObject::getHeight() const
{
	return height;
}

double GameObject::getTheta() const
{
	return theta;
}

int GameObject::getType() const
{
	return type;
}

bool GameObject::isCollidable() const
{
	return collidable;
}

bool GameObject::isAlive() const
{
	return alive;
}

// mutators
void GameObject::setX(const double &_x)
{
	x = _x;
}

void GameObject::setY(const double &_y)
{
	y = _y;
}

void GameObject::setZ(const double &_z)
{
	z = _z;
}

void GameObject::setWidth(const int &_width)
{
	width = _width;
}

void GameObject::setHeight(const int &_height)
{
	height = _height;
}

void GameObject::setTheta(const double &_theta)
{
	theta = _theta;
}

void GameObject::setCollidable(const bool &_collidable)
{
	collidable = _collidable;
}

// misc

//http://gamedev.stackexchange.com/questions/29786/a-simple-2d-rectangle-collision-algorithm-that-also-determines-which-sides-that
bool GameObject::checkCollision(GameObject *other, const double &deltaTime)
{
	double w = 0.5 * (width + other->width);
	double h = 0.5 * (height + other->height);
	double dx = x - other->x;
	double dy = y - other->y;

	return (abs(dx) <= w && abs(dy) <= h);
}

// spin object
void GameObject::tick(const double &deltaTime)
{
	theta += rotationRate * deltaTime;
	theta = (int)theta % 360;
}

// draw the object using the texture number stored in type
void GameObject::draw()
{
	double _x = width / 2.0;
	double _y = height / 2.0;

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER,0.1f);
	glBindTexture(GL_TEXTURE_2D, type);
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glColor4f(1.0f,1.0f,1.0f,1.0f);

	glTranslated(x, y , z);
	glRotated(theta, 0.0, 0.0, 1.0 );

	glBegin(GL_QUADS);
		glTexCoord2d(0.0,0.0); glVertex3d(-_x, -_y, z);
		glTexCoord2d(1.0,0.0); glVertex3d(_x, -_y, z);
		glTexCoord2d(1.0,1.0); glVertex3d(_x, _y, z);
		glTexCoord2d(0.0,1.0); glVertex3d(-_x, _y, z);
	glEnd();

	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

// draw lines around object to show where collision box is
void GameObject::drawDebug()
{
	if(!collidable)
		return;
	glPushMatrix();

	double w = width/2;
	double h = height/2;


	//glDisable(GL_TEXTURE_2D);
	glBegin(GL_LINES);

	glColor4f(0, 1.0f, 0, 1.0f);

	//verticle
	glVertex3d(x - w, y - h, 50);
	glVertex3d(x - w, y + h, 50);
	glVertex3d(x + w, y - h, 50);
	glVertex3d(x + w, y + h, 50);
	//horizontal
	glVertex3d(x - w, y - h, 50);
	glVertex3d(x + w, y - h, 50);
	glVertex3d(x - w, y + h, 50);
	glVertex3d(x + w, y + h, 50);
	glEnd();

	glPopMatrix();

}

// override this function in child classes
void GameObject::collide(GameObject *other)
{

}

void GameObject::die()
{
	alive = false;
}