/*
 * Name: Corey Dixon
 * Game Class Definition
 * Project Bullet Hell
 * Date: 3/12/2013
 * Description: Game class, creates GameObjects and stores them,
 *				maintains these objects, and deletes objects once
 *				they're dead. Uses a Quadtree to detection collision.
 *				calls tick on each GameObject, which drives the 
 *				behavior of each object, e.g. move. Calculates how
 *				long it takes the loop to complete (deltaTime).
 *				handles some user input. 
 *				
 */

#pragma once
#include <time.h>
#include "Quadtree.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Node.h"
#include "GameObject.h"
#include "Player.h"

class Game
{
public:
	// constructor
	Game(Keyboard *_keyboard, Mouse *_mouse);
	// destructor
	~Game(void);
	// accessor
	Node<GameObject>* getContainer();
	// misc
	void loop(); // calls game functions
private:
	void physics();
	void calculateDeltaTime();
	void handleInput();
	void add(GameObject*);
	void destroy(Node<GameObject>*);
	void killAll();
	bool outOfBounds(GameObject *obj);
	void createAsteroids();

	Node<GameObject> *container;
	Player *player;
	clock_t t;
	double deltaTime;
	double asteroidStormTime;
	bool asteroidsOn;
	bool asteroidsToggled;
	int objects, destroyed;
	Keyboard* keyboard;
	Mouse* mouse;
	Quadtree *quadtree;
};

