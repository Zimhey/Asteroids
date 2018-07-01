/*
 * Name: Corey Dixon
 * Mouse Class Definition
 * Project Bullet Hell
 * Date: 3/17/2013
 * Description: Similiar idea to the Keyboard class, however for a mouse.
 *				has an x, y for mouse location. only tracks x and y while
 *				they're inside the window. button 0 = left click,
 *				button 1 = right click, button 3 = scroll wheel click
 */

#pragma once
class Mouse
{
public:
	// constructor
	Mouse();
	// destructor
	~Mouse(void);
	// accessors
	bool getButtonState(const int &button) const;
	int getX() const;
	int getY() const;
	// mutators
	void setButtonState(const int &button, const bool &pressed);
	void setX(const int &_x);
	void setY(const int &_y);

private:
	bool *buttons;
	int x, y;
};

