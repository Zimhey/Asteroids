/*
 * Name: Corey Dixon
 * Keyboard Member Function Definitions
 * Project Bullet Hell
 * Date: 3/12/2013
 * Description: keyboard input, used to tell which keys are being pressed/not pressed.
 *				Implementation: creates an array of 256 bool's. each bool's index is
 *				its virtual key code / ASCII value. got idea from stack exchange, i can't remember exact
 *				location, but it was multiple stack exchange threads when i was searching for the way
 *				glut handled keyboards, which i found was they didn't, they suggested doing something
 *				like this.
 *				http://msdn.microsoft.com/en-us/library/windows/desktop/gg153546(v=vs.85).aspx
 *				main.cpp has a callback function when a key is pressed/ released which calls setKeyState
 *				using the virtual key code as the parameter to set that bool to true/false
 */

#include "keyboard.h"

// constructor
Keyboard::Keyboard()
{
	keys =  new bool[256];	// allocate

	for(int i = 0; i < 256; i++)
		keys[i] = false;	// set all to false
}

// destructor
Keyboard::~Keyboard()
{
	delete[] keys;	// deallocate
}
// accessors
bool Keyboard::getKeyState(const int &key) const
{
	return keys[key];
}

int Keyboard::keysPressed() const
{
	int total = 0;
	for( int i=0; i < 256; i++)
	{
		if(keys[i] == true)
			total++;
	}
	return total;
}

// mutators
void Keyboard::setKeyState(const int &key, const bool &pressed)
{
	keys[key] = pressed;
}

void Keyboard::toggleKeyState(const int &key)
{
	keys[key] = !keys[key];
}