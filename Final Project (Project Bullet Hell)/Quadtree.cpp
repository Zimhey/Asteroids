/*
 * Name: Corey Dixon
 * Quadtree Member Function Definitions
 * Project Bullet Hell
 * Date: 4/9/2013
 * Description: Quadtree's are recursive data structures used mostly in 2d Games.
 *				They are similiar to Binary Trees. Each Quadtree can have up to four
 *				child Quadtrees. Quadtrees represent a reagion in the cordinate plane.
 *				The child Quadtree will represent a quarter of that space. They will
 *				be located inside the parent in either the north west, north east,
 *				south west, or south east reagion. 
 *				Quadtree's make collision algorithims significantly more efficient.
 *				without a Quadtree the brute force method of collision is O(n^2)
 *				Quadtree's algorithim is closer to O(log n).
 *
 *				When adding an object to the Quadtree first we check how many objects
 *				we have. If we have more than maxObjects, we will attempt to move the
 *				object into a child Quadtree depending on where it is located. However
 *				if the object does not fit inside a child then we will add it to our 
 *				ObjectList. If the object is being added to the child Quadtree, it 
 *				will repeat this process, e.g. check how many objects we have and move
 *				down the tree as needed. 
 *				
 *				Every frame before we call collision then tick on every object, we call
 *				the update function. update is the sorting function. it is a recursive function
 *				it calls update on every Quadtree via the updateCaller function. Each Quadtree
 *				will check if every object is still inside this Quadtree using its location
 *				on the cordinate plane. if the object is not inside this quadtree, it will
 *				attempt to move the object to the parent. However if the parent is NULL
 *				it will stay in this tree. if a Quadtree has no objects its update, the parent
 *				will delete the empty child tree(assuming the child of the child has no objects)
 *				Objects MUST be sorted into the correct Quadtree in order for collision to work
*				correctly.
 *
 *				collision is another recursive function, it goes to the bottom nodes(leaf nodes)
 *				and begins to check every object in that Quadtree against eachother, once it has
 *				checked itself against every object in the current tree, it will test them against
 *				objects in the parent tree, and continue until it reaches the root node.
 *				if it finds a collision with two objects it will call collide on each object.
 *				each object defines its own behavior. 
 *				
 *				The draw function is also recursive and will draw a box around each Quadtree.
 *				this is for debugging so you can see where each tree is.
 *				
 *				When i started making this Quadtree i used 
 *				http://veeableful.wordpress.com/2012/02/07/algorithm-space-partitioning-using-quadtree/
 *				as a resource, however i have changed function that i started with and my Quadtree is very
 *				different from hers. However i did keep the naming of some things, and i liked her naming convention
 *				of adding an underscore for constructor variables and applied that to my constructors as well
 *				as my mutators for all classes. 
 */
#include "Quadtree.h"
#include "GameObject.h"
#include <windows.h>
#include <windowsx.h>
#include <gl/gl.h>
#include <gl/glu.h>
#pragma comment(lib,"opengl32.lib")

// constructor
Quadtree::Quadtree(double _x, double _y, double _width, double _height, int _level, Quadtree *_parent) :
	x		(_x),
	y		(_y),
	width	(_width),
	height	(_height),
	level	(_level),
	parent	(_parent)
{
	maxLevel = 0;
	maxObjects = 2;
	NW = NE = SW = SE = NULL;
}

// destructor
Quadtree::~Quadtree()
{
	if(NW != NULL)
		delete NW;
	if(NE != NULL)
		delete NE;
	if(SW != NULL)
		delete SW;
	if(SE != NULL)
		delete SE;
	NW = NE = SW = SE = NULL;
	
}

/* this is recursive function that belongs to clear()
*	it saves space by doing the not null check and calling clear()
*	then deleting the child, rather than having this same code
*	for each child */
void Quadtree::clearCaller(Quadtree *&child)
{
	if(child != NULL)
	{
		child->clear();
		delete child;
		child = NULL;
	}
}
/* recursively calls clearCaller() on each child 
*	then clears all objects in ObjectList */
void Quadtree::clear()
{
	clearCaller(NW);
	clearCaller(NE);
	clearCaller(SW);
	clearCaller(SE);

	objects.clear();

}

/* similiar to the clearCaller() this is a recursive function that belongs to update()
*	simply calls update on child if child exists, then deletes the child if it has no objects
*	hasObjects does child recursively through the child's children for objects, this way you
*	don't lose a Quadtree below the child */
void Quadtree::updateCaller(Quadtree *&child)
{
	if(child != NULL)
	{
		child->update();
		if(child->hasObjects() == false) // if child has no objects (recursively checks for objects in child's children)
		{
			delete child; // delete child
			child = NULL;
		}
	}
}

/* recursively calls updateCaller() on its children and then sorts
*	each object by checking if the object has moved out of this Quadtree's
*	reagion. If it has then it will move the object to the parent using the
*	addObject() function (addObject() will place the object in the correct Quadtree)
*	Also checks if the object is dead, if so removes it. Also checks if we have too
*	many objects, if so it attempts to move the object to a child. */
void Quadtree::update()	// make sure each object is inside quad
{
	// make sure child trees of child don't have objects

	updateCaller(NW);
	updateCaller(NE);
	updateCaller(SW);
	updateCaller(SE);

	GameObject **temp = objects.getObjects();		// get objects in quad

	if(temp != NULL)
	{
		for(int i = 0; i < objects.getCapacity(); i++)
		{
			temp = objects.getObjects();	//update temp

			if(temp[i] != NULL)
			{
				if(temp[i][0].isAlive() == false)	// if object is dead
				{
					objects.remove(i);
				}
				else if(!contains(temp[i]))			// is not inside this quad
				{
					if(parent != NULL)
					{
						parent->addObject(temp[i]);
						objects.remove(i);
					}
				}
				else		// is inside this quad
				{
					if(parent != NULL && !(parent->objects.getStored() > 0))	//parent doesn't have objects
					{
						parent->addObject(temp[i]);
						objects.remove(i);
					}
					else if(objects.getStored() >= maxObjects)	// too many objects in this quad
					{
						addToChild(temp[i]);		// move to child
						objects.remove(i);
					}
				}
			}
		}
	}

}

/* checks if the given object is colliding with any of the objects in
* the current Quadtree. This is used by collision() which traverses up the tree
* calling this function on each tree.*/
void Quadtree::checkCollision(GameObject *obj, double deltaTime)
{
	GameObject **temp = objects.getObjects();	// get our objects

	for(int i = 0; i < objects.getCapacity(); i++)	// for each of our objects
	{
		if(temp[i] != NULL && temp[i]->isCollidable() == true && temp[i] != obj) /* if object is not NULL
			and object is collidable and don't allow it to check collision with itself */
		{
			if(obj->checkCollision(temp[i], deltaTime))	// if they are colliding
			{
				obj->collide(temp[i]);	// call collision on both objects
				temp[i]->collide(obj);

				if(temp[i]->isAlive() == false)	// remove dead objects so we don't get dangling pointers
						objects.remove(i);
			}
		}
	}
}

void Quadtree::collision(double deltaTime)
{
	// go to leaf nodes
	if(NW != NULL)
		NW->collision(deltaTime);
	if(NE != NULL)
		NE->collision(deltaTime);
	if(SW != NULL)
		SW->collision(deltaTime);
	if(SE != NULL)
		SE->collision(deltaTime);

	//objects.sort();

	GameObject **temp = objects.getObjects();		// direct access to objects, avoid function calls

	if(temp != NULL)
		for(int i = 0; i < objects.getCapacity(); i++)	// get an object from this node
		{
			if(temp[i] != NULL && temp[i]->isCollidable() == true)	// make sure its not NULL and collidable
			{
				Quadtree *traverseP = this;	// start comparing it to objects in current node

				while (traverseP != NULL)	// traverse the tree, moving from here all the way to the root
				{
					traverseP->checkCollision(temp[i], deltaTime);	// call check collision on every Quadtree up to the root

					if(temp[i]->isAlive() == false)	// remove dead objects (checkCollision only removes the other object if dead)
					{
						objects.remove(i);
						break; // exit while loop and get a new object
					}
					traverseP = traverseP->parent;	// traverse to the parent and repeat
				}
			}

		}
}
/* checks if object fits inside a child region and moves it there. if it doesn't
*	fit in a child then add it to self*/
void Quadtree::addToChild(GameObject *object)
{
	if(contains(x, y, width / 2.0f, height / 2.0f, object))	// object is in top left
	{
		if(NW == NULL)	// NW doesn't exist yet
			NW = new Quadtree(x, y, width / 2.0f, height / 2.0f, level+1, this);	// create NW
		NW->addObject(object);	// add object to NW
		}
	else if(contains(x + width / 2.0f, y, width / 2.0f, height / 2.0f, object))	// top right
	{
		if(NE == NULL)
			NE = new Quadtree(x + width / 2.0f, y, width / 2.0f, height / 2.0f, level+1, this);
		NE->addObject(object);
	}
	else if(contains(x, y + height / 2.0f, width / 2.0f, height / 2.0f, object))	// bottom left
	{
		if(SW == NULL)
			SW = new Quadtree(x, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, this);
		SW->addObject(object);
	}
	else if(contains(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, object))	// bottom right
	{
		if(SE == NULL)
			SE = new Quadtree(x + width / 2.0f, y + height / 2.0f, width / 2.0f, height / 2.0f, level+1, this);
		SE->addObject(object);
	}
	else	// failed to add to child, add to self
	{
		objects.add(object);
	}
}
/* finds where to put the object given. attempts to move the object to child
*	if we have too many objects, if object is not in our reagion, move the object
*	to parent. else If this is the root node then add to self*/
void Quadtree::addObject(GameObject *object) 
{
  	if(contains(object))
	{
		if(objects.getStored() >= maxObjects)	// if more than max objects
		{
			addToChild(object);		// attempt to move to child quads
		}
		else
		{
			objects.add(object);	// else add to self
		}
	}
	else	// does not contain object
	{
		if(parent != NULL)	// if not the biggest quad
			parent->addObject(object);	// move to parent
		else
			objects.add(object);	// if parent quad add object
	}
}

/* recursively checks if children has objects*/
bool Quadtree::hasObjects()
{
	//if we have objects return true
	if(objects.getStored() > 0)
		return true;
	// recursively check children
	if(NW != NULL && NW->hasObjects() == true)
		return true;
	if(NE != NULL && NE->hasObjects() == true)
		return true;
	if(SW != NULL && SW->hasObjects() == true)
		return true;
	if(SE != NULL && SE->hasObjects() == true)
		return true;
	return false;
}

// checks if object is inside this quad
bool Quadtree::contains(GameObject *object) 
{
	return contains(x, y, width, height, object);
}
// checks inside child quad
bool Quadtree::contains(Quadtree *child, GameObject *object) 
{
	return contains(child->x, child->y, child->width, child->height, object);
}
// checks if object is inside of cordinates you give
bool Quadtree::contains(double _x, double _y, double _width, double _height, GameObject *object)
{
	return !(object->getX() -object->getWidth() /2 < _x || // left side
		object->getY() - object->getHeight() /2 < _y || // top side
		object->getX() + object->getWidth() /2 > _x + _width || // right side
		object->getY() + object->getHeight() /2 > _y + _height // bottom side
		);
}
/* recursive draw function to draw the reagion of each Quadtree
*	changes the color based on how many objects are in the tree
*	white = empty, blue = at least one, red at least maxObjects*/
void Quadtree::draw() 
{
	if(NW != NULL)
		NW->draw();
	if(NE != NULL)
		NE->draw();
	if(SW != NULL)
		SW->draw();
	if(SE != NULL)
		SE->draw();

	//draw tree
	glPushMatrix();
	glColor4f(1.0f,1.0f,1.0f,1.0f);		// white
	if(objects.getStored() > 0)
		glColor4f(0 ,0.0f,1.0f,1.0f);	// blue
	if(objects.getStored() >= maxObjects)
		glColor4f(1.0f , 0, 0,1.0f);	// red

	glEnable(GL_DEPTH_TEST);
	glDepthMask(TRUE);

	glBegin(GL_LINES);
		//verticle
		glVertex3d(x, y, 90);
		glVertex3d(x, y + height, 90);
		glVertex3d(x + width, y, 90);
		glVertex3d(x + width, y + height, 90);
		//horizontal
		glVertex3d(x, y, 90);
		glVertex3d(x + width, y, 90);
		glVertex3d(x, y + height, 90);
		glVertex3d(x + width, y + height, 90);
	glEnd();
	glPopMatrix();
}