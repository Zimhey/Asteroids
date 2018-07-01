/*
 * Name: Corey Dixon
 * ObjectList Class Definition
 * Project Bullet Hell
 * Date: 4/28/2013
 * Description: Dynamic array class for use in the Quadtree
 *				NO DEALLOCATION OF OBJECTS IS DONE HERE. Linked List will
 *				handle all deallocation of objects.
 */

#pragma once
#include "GameObject.h"
#include <stddef.h>	// for NULL
class ObjectList
{
public:
	// constructor
	ObjectList(void);
	// destructor
	~ObjectList(void);
	// accessors
	int getCapacity() const;
	int getStored() const;
	GameObject** getObjects() const;
	GameObject* getObject(int i);
	// misc
	void add( GameObject *object);
	void remove(int index);
	void remove( GameObject *object);
	void sort();
	void clear();
private:
	GameObject **objects;
	int capacity;
	int stored;
};

