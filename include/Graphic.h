#ifndef __GRAPHIC__
#define __GRAPHIC__

#include <MLV/MLV_all.h>
#include "Quadtree.h"

#define MAX_SCREEN_X 1080
#define MAX_SCREEN_Y 720
#define MAXPIXEL 512

/**
 * Draw an image represented by the MLV_Image structure
 * on the center of the window
 * @param img a pointor to a MLV_Image structure
 */
void draw_center_image(MLV_Image* img);

/**
 * Draw the image represented by a Quadtree structure with a certain position
 * on the window.
 * @param origin_x the position of the image in the X axis
 * 		  origin_y the position of the image in the Y axis
 * 		  qt a Quadtree structure
 */
void graphic_quadtree(int origin_x, int origin_y, Quadtree qt);

#endif
