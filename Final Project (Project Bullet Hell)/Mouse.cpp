/*
 * Name: Corey Dixon
 * Mouse Member Function Definitions
 * Project Bullet Hell
 * Date: 3/17/2013
 * Description: Similiar idea to the Keyboard class, however for a mouse.
 *				has an x, y for mouse location. only tracks x and y while
 *				they're inside the window. button 0 = left click,
 *				button 1 = right click, button 2 = scroll wheel click
 */

#include "Mouse.h"

// constructor
Mouse::Mouse()
{
	buttons = new bool[3];	// allocate

	for(int i = 0; i < 3; i++)	// initialize
		buttons[i] = false;
	y = x = 0;
}

// destructor
Mouse::~Mouse(void)
{
	delete [] buttons;	// deallocate
}

// accessors
bool Mouse::getButtonState(const int &button) const
{
	return buttons[button];
}

int Mouse::getX() const
{
	return x;
}

int Mouse::getY() const
{
	return y;
}

// mutators
void Mouse::setButtonState(const int &button, const bool &pressed)
{
	buttons[button] = pressed;
}

void Mouse::setX(const int &_x)
{
	x = _x;
}

void Mouse::setY(const int &_y)
{
	y = _y;
}