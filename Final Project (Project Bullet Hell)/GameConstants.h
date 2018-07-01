/*
 * Name: Corey Dixon
 * Constants used by most classes
 * Project Bullet Hell
 * Date: 3/30/2013
 * Description: has the game's width & height
 *				also has the types for objects
 *				the reason they're integers is
 *				LoadTexture in main.cpp returns
 *				integers for each texture, to
 *				use that texture for drawing 
 *				you need that integer. These
 *				integers are incremented
 *				everytime you load a texture.
 *				so rather than storing the
 *				values returned from LoadTexture
 *				i just have the integers in order
 *				of what i load.
 *				oh and it has PI.
 */

#pragma once
const int gameWidth = 1280;
const int gameHeight = 720;
// textures/types
const unsigned int ship = 1;
const unsigned int projectile = 2;
const unsigned int background = 3;
const unsigned int asteroid1 = 4;
const unsigned int enemy_ship = 5;
const unsigned int enemy_projectile = 6;
const unsigned int error = 7;
const unsigned int defeat = 8;

const double PI = 3.141592653589793238462;