/*
 * Name: Corey Dixon
 * PlayerProjectile Class Definition
 * Project Bullet Hell
 * Date: 5/15/2013
 * Description: derived from Projectile class, changes nothing but the texture(type).
 */

#pragma once
#include "Projectile.h"
class PlayerProjectile :
	public Projectile
{
public:
	PlayerProjectile(double _x, double _y);
	PlayerProjectile(double _x, double _y, double destX, double destY);
	PlayerProjectile(double _x, double _y, double destX, double destY, int speed);
	~PlayerProjectile(void);

	void collide(GameObject *other);
};

