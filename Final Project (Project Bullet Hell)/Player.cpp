/*
 * Name: Corey Dixon
 * Player Member Function Definitions
 * Project Bullet Hell
 * Date: 4/29/2013
 * Description: Player class derived from Entity. handles some input
 *				uses the ship texture, ship always points towards mouse
 *				holds when the ship last shot a projectile. projectile
 *				creation done in Game class. collide changed
 *				Player only collides with Asteroids. (will add EnemyProjectile collision soon).
 */

#include "Player.h"
#include "Asteroid.h"
#include "Projectile.h"
#include <math.h>

// constructors
Player::Player(Keyboard *_keyboard)
{
	keyboard = _keyboard;
	x = gameWidth /2;
	y = gameHeight /2;
	width = 96;
	height = 96;
	type = 1;
	collidable = true;
	alive = true;
	lastShotTime = velocityX = velocityY = 0;
	health = 200;
}

Player::Player(Keyboard *_keyboard, Mouse *_mouse)
{
	keyboard = _keyboard;
	mouse = _mouse;
	x = gameWidth /2;
	y = gameHeight /2;
	width = 96;
	height = 96;
	type = 1;
	collidable = true;
	alive = true;
	lastShotTime = velocityX = velocityY = 0;
	health = 200;
}

// destructor
Player::~Player(void)
{
}
// accessors
double Player::getLastShotTime() const
{
	return lastShotTime;
}
// mutators
void Player::setLastShotTime(const double &_lastShotTime)
{
	lastShotTime = _lastShotTime;
}
void Player::justShot()
{
	lastShotTime = 0;
}
// misc
void Player::tick(const double &deltaTime)
{
	lastShotTime += deltaTime;

	theta = atan2(mouse->getY() - y, mouse->getX() - x);
	theta *= (180/ 3.141592653589793238462);
	theta += 90.0;

	handleInput(deltaTime);

	Entity::tick(deltaTime);
}

void Player::move(const double &deltaTime)
{

	x += velocityX * deltaTime;
	y += velocityY * deltaTime;
	// keep player from moving off screen
	if(y < 0)
		y = 0;
	else if(y > gameHeight)
		y = gameHeight;
	if(x < 0)
		x = 0;
	else if(x > gameWidth)
		x = gameWidth;
}

void Player::handleInput(double deltaTime)
{
	const int speed = 500*4;
	const int speedCap = 500;
	const double slowSpeed = 0.90 - deltaTime;

	if(keyboard->getKeyState('W') == true || keyboard->getKeyState('w') == true)
		if(keyboard->getKeyState('S') == true || keyboard->getKeyState('s') == true)	// both being pressed
			velocityY *= slowSpeed;	// slow down
		else
			velocityY -=speed * deltaTime;	// just w being pressed
	else if(keyboard->getKeyState('S') == true || keyboard->getKeyState('s') == true)
		velocityY +=speed * deltaTime;		// just s being pressed
	else if(keyboard->getKeyState('W') == false || keyboard->getKeyState('w') == false)	// if neither is being pressed
		velocityY *= slowSpeed;	// slow down


	if(keyboard->getKeyState('D') == true || keyboard->getKeyState('d') == true)
		if(keyboard->getKeyState('A') == true || keyboard->getKeyState('a') == true)	// both being pressed
			velocityX *= slowSpeed;	// slow down
		else
			velocityX += speed * deltaTime;	// just d being pressed
	else if(keyboard->getKeyState('A') == true || keyboard->getKeyState('a') == true)
		velocityX -=speed * deltaTime;		// just a being pressed
	else if(keyboard->getKeyState('D') == false || keyboard->getKeyState('d') == false)	// if neither is being pressed
		velocityX *= slowSpeed;	// slow down

	if(velocityY > speedCap)
		velocityY = speedCap;
	else if(velocityY < -speedCap)
		velocityY = -speedCap;
	if(velocityX > speedCap)
		velocityX = speedCap;
	else if(velocityX < -speedCap)
		velocityX = -speedCap;
}

void Player::collide(GameObject *other)
{
	if(other->getType() == asteroid1)
	{
		Asteroid *ast = &static_cast<Asteroid&>(*other);
		velocityX += ast->getVeloX();
		velocityY += ast->getVeloY();
		health -= 50;
	}
	if(other->getType() == enemy_projectile)
		health -=34;
}