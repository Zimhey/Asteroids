/*
 * Name: Corey Dixon
 * Game Member Function Definitions
 * Project Bullet Hell
 * Date: 3/12/2013
 * Description: Game class, Objects are stored in a doubly linked list
 *				using the template class Node. Objects are also
 *				stored inside the quadtree. Quadtrees will remove
 *				an object before it is deleted in the destroy 
 *				function, more information inside destroy &
 *				the Quadtree class. 
 *				
 */
#include <windows.h>
#include <math.h>

#include "GameConstants.h"
#include "Game.h"
#include "Projectile.h"
#include "PlayerProjectile.h"
#include "Asteroid.h"
#include "NPC.h"
#include "NPCProjectile.h"
#include "DefeatMsg.h"

// constructor
Game::Game(Keyboard *_keyboard, Mouse *_mouse)
{
	keyboard = _keyboard;
	mouse = _mouse;
	asteroidsToggled = asteroidsOn = false;
	asteroidStormTime = 0;
	deltaTime = 0;
	objects = destroyed = 0;
	t = clock();
	container = NULL;
	quadtree = new Quadtree( 0, 0, gameWidth, gameHeight, 0, NULL );
	player = new Player(keyboard, mouse);
	add(player);
}

// destructor
Game::~Game(void)
{
	Node<GameObject> *traverseP = container;
	while(traverseP != NULL)
	{
		Node<GameObject> *del = traverseP;
		traverseP = traverseP->next;
		destroy(del);
	}
	container = NULL;
	delete quadtree;
	quadtree = NULL;
}

// main game loop, calls all important functions for the game
void Game::loop()
{
	if(player == NULL)	// other functions depend on having a player, make sure we have one
	{
		player = new Player(keyboard, mouse);
		add(player);
		add(new DefeatMsg);
	}

	calculateDeltaTime();
	handleInput();
	quadtree->update();
	quadtree->collision(deltaTime);
	quadtree->draw();
	physics();
}

/* Physics function creates asteroids, deletes dead objects
*	and calls tick on every object. pauses game when C is pressed*/
void Game::physics()
{
	// pasue if C is being pressed.
	if(keyboard->getKeyState('C') == true || keyboard->getKeyState('c') == true)
	{
		Node<GameObject> *traverseP = container;
		while( traverseP != NULL)	// draw all the objects
		{							// without this loop objects would not be drawn while paused
			traverseP->obj->draw();
			traverseP->obj->drawDebug();
			traverseP = traverseP->next;
		}
		return;
	}

	createAsteroids();
	
	Node<GameObject> *traverseP = container;

	while( traverseP != NULL)
	{
		GameObject *obj = traverseP->obj;

		if(obj->isAlive() == false)	// delete dead objects, (MUST COME BEFORE KILLING AN OBJECT.)
		{							// killing the object after the check lets the quadtree remove dead objects before deletion
			Node<GameObject> *del = traverseP;
			traverseP = traverseP->next;
			destroy(del);
			continue;
		}

		// check if object is outofbounds
		if(outOfBounds(obj) == true)
			obj->die();
		else
			obj->tick(deltaTime);	// tick each object, object will define its own behavior, e.g. move

		obj->draw();
		obj->drawDebug();

		// next obj
		traverseP = traverseP->next;
	}

}
/* Creates Objects depending on player input, kills all objects if E is pressed
*	majority of objects being created here are for debug purposes. Obviously
*	you won't be able to kill all objects in the final game*/
void Game::handleInput()
{

	if(keyboard->getKeyState('E') == true || keyboard->getKeyState('e') == true)	// e
		killAll();

	if(keyboard->getKeyState(' ') == true)	// space
	{
		if(player->getLastShotTime() > 0.05)
		{
			for(int i = 0; i < 25; i++)
				add( new PlayerProjectile(player->getX(), player->getY(), rand() % 1280, rand() % 720));
			player->justShot();
		}
	}
	if(mouse->getButtonState(0) == true)	// left mouse
	{
		if(player->getLastShotTime() > 0.05)
		{
			add( new PlayerProjectile(player->getX(), player->getY(), mouse->getX(), mouse->getY()));
			player->justShot();
		}
	}
	if(mouse->getButtonState(1) == true)	// right mouse
	{
		if(player->getLastShotTime() > 0.10)
		{
			add( new PlayerProjectile(mouse->getX(), mouse->getY()));
			player->justShot();
		}
	}
	if(keyboard->getKeyState('Q') == true || keyboard->getKeyState('q') == true)	
	{
		if(player->getLastShotTime() > 0.25)
		{
			add(new Asteroid(mouse->getX(), mouse->getY()));	// asteroid on mouse location
			player->justShot();
		}
	}
	if(keyboard->getKeyState('X') == true || keyboard->getKeyState('x') == true)
	{
		if(player->getLastShotTime() > 0.25)
		{
			add(new NPCProjectile(mouse->getX(), mouse->getY()));	// enemy projectile on mouse location
			player->justShot();
		}
	}
	if(keyboard->getKeyState('Z') == true || keyboard->getKeyState('z') == true)
	{
		if(player->getLastShotTime()  > 0.25)
		{
			add(new NPC(mouse->getX(), mouse->getY()));				// enemy on mouse location
			player->justShot();
		}
	}

	if(keyboard->getKeyState('R') == true || keyboard->getKeyState('r') == true)
	{
		if(!asteroidsToggled)
			asteroidsOn = !asteroidsOn;				// toggles asteroid storm on and off
		asteroidsToggled = true;
	}
	else
		asteroidsToggled = false;

}

// creates asteroids off screen and sends them towards the screen
void Game::createAsteroids()
{
	asteroidStormTime += deltaTime;	// time since we last created an asteroid

	if(asteroidsOn)
	{
		if(asteroidStormTime > 0.15)	// if it has been at least 0.15 of a screen
		{
			int startX, startY;	// where object will be created
			if(rand() % 2 == 0)
				startX = (rand() % gameWidth) + gameWidth;
			else
				startX = -(rand() % gameWidth);

			if(rand() % 2 == 0)
				startY = (rand() % gameHeight) + gameHeight;
			else
				startY = -(rand() % gameHeight);

			add( new Asteroid(startX, startY, rand() % gameWidth, rand() % gameHeight));
			asteroidStormTime = 0;	// set time since we last created an asteroid to 0
		}
	}
}

// checks if given object are out of bounds
bool Game::outOfBounds(GameObject *obj)
{
	if(obj->getType() == projectile)	// projectiles go out of bound when off screen
	{
		return (obj->getX() +obj->getWidth() < 0 ||  // left
			obj->getY() +obj->getHeight() < 0 || // top
			obj->getX() -obj->getWidth() > gameWidth || // right
			obj->getY() -obj->getHeight() > gameHeight); // bottom
	}
	else if(obj->getType() == asteroid1)	// asteroids get more space
	{
		return (obj->getX() < -gameWidth ||	// left
			obj->getY() < -gameHeight ||	// top
			obj->getX() > gameWidth * 2 ||	// right
			obj->getY() > gameHeight * 2);	// bottom
	}

	return false;
}

// add objects to the beginning of the linked list
void Game::add(GameObject *obj)
{
	objects++;

	quadtree->addObject(obj);	// add object to root of quadtree (quadtree will handle from there)

	if(container != NULL)	// if we have a list
	{
		container->prev = new Node<GameObject>(obj);	// add the new node
		container->prev->next = container;	// set up chain
		container = container->prev;	// container starts at the new node
	}
	else
		container = new Node<GameObject>(obj);	// create the list
}

/* deletes a node and object, regardless of position in list.
*	be careful at what point you call this function. game should
*	loop once with the object dead before calling this function
*	objects will be removed from Quadtree's List if they are dead
*	during its update. if you delete it before it has been removed
*	from the quadtree, it will leave a dangling pointer and crash
*	the game.*/
void Game::destroy(Node<GameObject> *node)
{
	destroyed++;	// for early debugging
	if(node->obj == player)	// if obj is player
		player = NULL;		// don't leave a dangling pointer
	if(node->prev != NULL)	// if we have a previous node
		node->prev->next = node->next;	// fix chain
	if(node->next != NULL)	// if we have a next node
			node->next->prev = node->prev;	// fix chain
	if(node == container)	// if deleting container
		container = node->next;	// move to next node. also makes container null if last node

	delete node->obj;
	delete node;
}

// traverses the linked list calling die() on each object
void Game::killAll()
{
	Node<GameObject> *traverseP = container;
	while(traverseP != NULL)
	{
			traverseP->obj->die();
		traverseP = traverseP->next;
	}
}

// calculated the amount of time it takes for the game to loop
void Game::calculateDeltaTime()
{
	deltaTime = ((double)(clock() -t)) / 1000;	// converts to seconds. e.g. 1 = 1 second, 0.1 = a tenth of a second
	t = clock();	// start a new clock
}

// accessor
Node<GameObject>* Game::getContainer()	// this was used by main at one 
{										// point to get all the objects for drawing.
	return container;					// However isn't used anymore.
}