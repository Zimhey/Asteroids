/*
 * Name: Corey Dixon
 * Asteroid Member Function Definitions
 * Project Bullet Hell
 * Date: 4/30/2013
 * Description: Asteroid class used by game to create asteroids
 *				that fly across the screen
 */
#include "Asteroid.h"
#include <stdlib.h>
#include <math.h>

// constructors
Asteroid::Asteroid(double _x, double _y)
{
	x = _x;
	y = _y;
	z = 0;
	theta = rand() % 360;
	width = height = (rand() % 64+16)+16;
	type = asteroid1;
	alive = true;
	velocityX = velocityY = 0;
	health = (width + height) * 2;
	if(rand() % 2 == 0)
		rotationRate = rand() % 350;
	else
		rotationRate = -(rand() % 350);
}

Asteroid::Asteroid(double _x, double _y, double destX, double destY)
{
	x = _x;
	y = _y;
	z = 0;
	theta = rand() % 360;
	width = height = (rand() % 64+16)+16;
	type = asteroid1;
	alive = true;
	int speed = (rand() % 500) + 200;
	double angle = atan2(destY - y, destX - x);
	angle *= (180/ PI);
	velocityX = cos( angle * PI / 180) * speed;
	velocityY = sin( angle * PI / 180) * speed;
	health = (width + height) * 2;
	if(rand() % 2 == 0)
		rotationRate = rand() % 350;
	else
		rotationRate = -(rand() % 350);
}

// destructor
Asteroid::~Asteroid(void)
{
}

// misc

void Asteroid::tick(const double &deltaTime)
{
	oldVelocityX = velocityX;
	oldVelocityY = velocityY;

	if(health < 0)
		die();
	else
		move(deltaTime);
}

void Asteroid::move(const double &deltaTime)
{
	theta += rotationRate * deltaTime;

	lastX = x;
	lastY = y;
	oldVelocityX = velocityX;
	oldVelocityY = velocityY;

	x += velocityX  * deltaTime;
	y += velocityY  * deltaTime;
}

void Asteroid::undoMove()
{
	x = lastX;
	y = lastY;
}

void Asteroid::collide(GameObject *other)
{
	if(other->getType() == projectile)
	{
		die();
		return;
		Moveable *obj =  &static_cast<Moveable&>(*other);
		//velocityX += obj->getVeloX() * 0.25;
		//velocityY += obj->getVeloY() * 0.25;
		//health -= 150;
	}
	if(other->getType() == enemy_projectile)
		die();
	if(other->getType() == ship)
		die();
	if(other->getType() == enemy_ship)
		die();
	if(other->getType() == asteroid1)
	{
		Asteroid *obj =  &static_cast<Asteroid&>(*other);


		// none of this works because checkCollision in moveable does not correctly determine
		// if objects will collide after the next move correctly
		// so objects will touch eachother and call this function indefinitely

/*		if(velocityX == oldVelocityX && velocityY == oldVelocityY)
		{
			velocityX *= -1;
			velocityY *= -1;
		}

		if(GameObject::checkCollision(other, 0))
		{
			undoMove();
			obj->undoMove();
		}*/

/*
		velocityX = -oldVelocityY;
		velocityY = -oldVelocityX;

		obj->setVeloX(-obj->oldVelocityY);
		obj->setVeloY(-obj->oldVelocityX); */

		/*double xDiff = (x + oldVelocityX) - (obj->getX() + obj->oldVelocityX);
		double yDiff = (y + oldVelocityY) - (obj->getY() + obj->oldVelocityY);
		double collisionAngle = atan2(yDiff, xDiff);

		double magnitude1 = sqrt(pow(oldVelocityX, 2) + pow(oldVelocityY, 2)) * 0.9;
		double magnitude2 = sqrt(pow(obj->oldVelocityX, 2) + pow(obj->oldVelocityY, 2)) * 0.9;

		if(magnitude1 < 0.2)
			magnitude1 = 0;
		if(magnitude2 < 0.2)
			magnitude2 = 0;

		double direction1 = atan2(oldVelocityY, oldVelocityX);
		double direction2 = atan2(obj->oldVelocityY, obj->oldVelocityX);

		double newXSpeed1 = magnitude1 * cos(direction1 -collisionAngle);
		double newYSpeed1 = magnitude1 * sin(direction1 -collisionAngle);
		double newXSpeed2 = magnitude2 * cos(direction2 -collisionAngle);
		double newYSpeed2 = magnitude2 * sin(direction2 -collisionAngle);
		
		velocityX = cos(collisionAngle) * newXSpeed2 + cos(collisionAngle + PI /2) * newYSpeed1;
		velocityX = sin(collisionAngle) * newXSpeed2 + sin(collisionAngle + PI /2) * newYSpeed1;

		obj->setVeloX(cos(collisionAngle) * newXSpeed1 + cos(collisionAngle + PI / 2) * newYSpeed2);
		obj->setVeloY(sin(collisionAngle) * newXSpeed1 + sin(collisionAngle + PI / 2) * newYSpeed2);
		*/
	}
}