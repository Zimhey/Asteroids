/*
 * Name: Corey Dixon
 * Player Class Definition
 * Project Bullet Hell
 * Date: 4/29/2013
 * Description: Player class derived from Entity. handles some input
 *				uses the ship texture, ship always points towards mouse
 *				holds when the ship last shot a projectile. projectile
 *				creation done in Game class. collide changed
 *				Player only collides with Asteroids. (will add EnemyProjectile collision soon).
 */

#pragma once
#include "Entity.h"
#include "Keyboard.h"
#include "Mouse.h"

class Player :
	public Entity
{
public:
	// constructors
	Player(Keyboard *_keyboard);
	Player(Keyboard *_keyboard, Mouse *_mouse);
	// destructor
	~Player(void);
	// accesors
	double getLastShotTime() const;
	// mutators
	void setLastShotTime(const double &_lastShotTime);
	void justShot();
	// misc
	void move(const double &deltaTime);
	void tick(const double &deltaTime);
	void collide(GameObject *other);
protected:
	Keyboard *keyboard;
	Mouse *mouse;
	void handleInput(double deltaTime);
	double lastShotTime;
};

