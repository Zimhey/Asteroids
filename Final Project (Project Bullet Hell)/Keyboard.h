/*
 * Name: Corey Dixon
 * Keyboard Class Definition
 * Project Bullet Hell
 * Date: 3/12/2013
 * Description: keyboard input, used to tell which keys are being pressed/not pressed.
 */
#pragma once

class Keyboard
{
public:
	// constructor
	Keyboard();
	// destructor
	~Keyboard();
	// accessors
	bool getKeyState(const int &key) const;
	int keysPressed() const;
	// mutators
	void setKeyState(const int &key, const bool &pressed);
	void toggleKeyState(const int &key);
private:
	bool* keys;
};
