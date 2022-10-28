#ifndef __ACTIONS__
#define __ACTIONS__

#include "Quadtree.h"
#include "Image.h"

/**
 * @brief Enum that specify the action that can be done by the user
 */
typedef enum {
	SELECT = 0,
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
 * @brief Execute an action according to the specified action.
 * This action can impact an Image structure and a 
 * Quadtree structure
 * @param action the specified action
 * @param info a pointor to an Image structure
 * @param qt a pointor to a Quadtree structure
 */
void choice(Action action, Image* info, Quadtree* qt);

#endif
