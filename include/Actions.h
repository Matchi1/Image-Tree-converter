#ifndef __ACTIONS__
#define __ACTIONS__

#include "Quadtree.h"
#include "Image.h"

/**
 * Enum that specify the action that can be done
 * by the user
 */
typedef enum {
	SELECT,
	SAVE_N,
	SAVE_C,
	MIN,
	SAVE_MIN_N,
	SAVE_MIN_C,
	TEST,
	QUIT,
	NONE
}Action;

/**
 * Execute an action according to the specified action.
 * This action can impact an Image structure and a 
 * Quadtree structure
 * @param action the specified action
 * 		  info a pointor to an Image structure
 * 		  qt a pointor to a Quadtree structure
 */
void choice(Action action, Image* info, Quadtree* qt);

#endif
