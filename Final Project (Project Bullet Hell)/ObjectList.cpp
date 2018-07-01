/*
 * Name: Corey Dixon
 * ObjectList Member Function Definitions
 * Project Bullet Hell
 * Date: 4/28/2013
 * Description: Dynamic array class for use in the Quadtree
 *				NO DEALLOCATION OF OBJECTS IS DONE HERE. Linked List will
 *				handle all deallocation of objects.
 */

#include "ObjectList.h"

// constructor
ObjectList::ObjectList(void)
{
	capacity = 10;
	stored = 0;
	objects = NULL;
}
// destructor
ObjectList::~ObjectList(void)
{
	clear();
}
// accessors
int ObjectList::getCapacity() const
{
	return capacity;
}

int ObjectList::getStored() const
{
	return stored;
}

GameObject** ObjectList::getObjects() const
{
	return objects;
}

GameObject* ObjectList::getObject(int i)
{
	return objects[i];
}

// misc
void ObjectList::add(GameObject *object)	// adds an object to the array
{

	if(objects == NULL)	// allocate an array
	{
		objects = new GameObject *[capacity];
		for(int i = 0; i < capacity; i++)	// set each element to null
			objects[i] = NULL;
	}
	if(stored > capacity * 0.90)	// if we're close to full
	{
		sort();	/* sort the array so all objects are at the beginning of the array
					 without sort, we might not copy all the objects when using
					 stored in the for loop */

		GameObject **temp = objects;	// store current pointer to our array
		capacity *= 2;		// double the capacity
		objects = new GameObject *[capacity];	// allocate the new array

		for(int i = 0; i < stored; i++)		// move objects to new array
			objects[i] = temp[i];
		for(int i = stored; i < capacity; i++)	// make the rest NULL
			objects[i] = NULL;
		delete temp;				// deallocate the old array
	}
	for(int i = 0; i < capacity; i++)	// find an empty location to store object
	{
		if(objects[i] == NULL)
		{
			objects[i] = object;		// store object
			stored++;
			break;					// exit loop
		}
	}
}

void ObjectList::remove(int index) // set object at index to NULL
{
	if(objects[index] != NULL)
	{
		objects[index] = NULL;
		stored--;
	}
}

void ObjectList::remove(GameObject *object) // find object in array and set it to NULL
{
	for(int i = 0; i < capacity; i++)
	{
		if(objects[i] == object)
		{
			objects[i] = NULL;
			stored--;
			break;
		}
	}
}

void ObjectList::sort()	// moves all objects to the beginning of the array
{
	if(objects != NULL)	//if we have objects

		for(int i = 0; i < stored; i++)	// make sure objects are at the bottom of the list
		{
			if(objects[i] == NULL && i+1 <= capacity)	// if we find NULL and aren't the last object in array
			{
				if(objects[i + 1] != NULL) // if next object exists, move it down.
				{
					objects[i] = objects[i + 1];
					objects[i + 1] = NULL;
				}
				else		// else find the next object and move it down
					for(int j = i + 2; j < capacity; j++)
						if(objects[j] != NULL)
						{
							objects[i] = objects[j];
							objects[j] = NULL;
							break;	//break when we find an object
						}
			}
		}
}

void ObjectList::clear()	// set all pointers to NULL and delete our array
{
	if(objects == NULL)
		return;

	for(int i = 0; i < capacity; i++)
		objects[i] = NULL;
	stored = 0;
	delete objects;
	objects = NULL;
}