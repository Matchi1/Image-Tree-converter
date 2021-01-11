#ifndef __GRAPHIC__
#define __GRAPHIC__

#include <MLV/MLV_all.h>
#include "Quadtree.h"

#define MAX_SCREEN_X 1080
#define MAX_SCREEN_Y 720
#define MAXPIXEL 512

void graphic_quadtree(int origin_x, int origin_y, int length, Quadtree qt);

#endif
