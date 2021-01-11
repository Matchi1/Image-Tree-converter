#ifndef __ACTIONS__
#define __ACTIONS__

#include "Quadtree.h"
#include "Image.h"

typedef enum {
	SELECT,
	SAVE_N,
	SAVE_C,
	MINIMI,
	QUIT,
	NONE
}Action;

void choice(Action action, Image* info, Quadtree* qt);

#endif
