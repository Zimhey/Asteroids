/*
 * Name: Corey Dixon
 * NPCProjectile Class Definition
 * Project Bullet Hell
 * Date: 5/15/2013
 * Description: derived from Projectile, doesn't change much other than it now
 *				uses the enemy_projectile texture.
 */

#pragma once
#include "Projectile.h"

class NPCProjectile :
	public Projectile
{
public:
	NPCProjectile(double _x, double _y);
	NPCProjectile(double _x, double _y, double destX, double destY);
	NPCProjectile(double _x, double _y, double destX, double destY, int speed);
	~NPCProjectile(void);

	void collide(GameObject *other);
};

