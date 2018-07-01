/*
 * Name: Corey Dixon
 * Quadtree Class Definition
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


#pragma once
#include "GameObject.h"
#include "ObjectList.h"

class Quadtree
{
public:
	// constructor
	Quadtree(double x, double y, double width, double height, int level, Quadtree *_parent);
	// destructor
	~Quadtree(void);
	// misc
	void addObject(GameObject *object);
	void update();
	void collision(double deltaTime);
	void clear();
	void draw();
private:
	double x, y, width, height;
	int level, maxLevel, maxObjects;
	Quadtree *parent;
	Quadtree *NW;
	Quadtree *NE;
	Quadtree *SW;
	Quadtree *SE;
	ObjectList objects;
	void addToChild(GameObject *object);
	bool hasObjects();
	void checkCollision(GameObject *obj, double deltaTime);
	void updateCaller(Quadtree *&child);
	void clearCaller(Quadtree *&child);
	bool contains(Quadtree *child, GameObject *object);
	bool contains(double x, double y, double width, double height, GameObject *object);
	bool contains( GameObject *object);
};

