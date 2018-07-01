/*
 * Name: Corey Dixon
 * NPC Class Definition
 * Project Bullet Hell
 * Date: 4/29/2013
 * Description: for enemy ships. WIP (not implemented yet) currently just creates
 *				an object with the enemy_ship texture
 */

#pragma once
#include "Entity.h"

class NPC :
	public Entity
{
public:
	// constructor
	NPC(double _x, double _y);
	// destructor
	~NPC(void);
	// misc
	void collide(GameObject *other);
private:
	void ai();
};

