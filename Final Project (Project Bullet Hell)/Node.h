/*
 * Name: Corey Dixon
 * Node Class Definition & Member Function Definitions (can't split template classes into a header and implementation file for some reason?)
 * Project Bullet Hell
 * Date: 3/14/2013
 * Description: Class for a linked list Node rather than a structure.
 *				having a constructor is nice!
 */

#pragma once
#include <cstdlib>	// FOR NULL. WHY ISN'T NULL STANDARD?!?!

template <class T>
class Node
{
public:
	Node(void)
	{
		obj = NULL;
		next = NULL;
		prev = NULL;
	};

	Node(T *_obj)
	{
		obj = _obj;
		next = NULL;
		prev = NULL;
	};

	Node(T *_obj, Node<T> *_prev)
	{
		obj = _obj;
		prev = _prev;
		next = NULL;
	};

	Node(T *_obj, Node<T> *_prev, Node<T> *_next)
	{
		obj = _obj;
		prev = _prev;
		next = _next;
	}

	~Node(void)
	{
		// used to delete the object with it, however that changed when creating the Quadtree
	};

	// public so i can modify variables directly. (could add functions to do this if i wanted to(might do this later))
	T *obj;
	Node<T> *next;
	Node<T> *prev;
};