#ifndef __INPUT_IMG__
#define __INPUT_IMG__

#include <MLV/MLV_all.h>
#include "Quadtree.h"

/**
 * Convert an image into a Quadtree structure
 * @param img a pointor to MLV_Image structure
 * 	      qt a pointor to a Quadtree structure
 * @return 0 if an error occurred else 1
 */
int convert_img_qt(MLV_Image* img, Quadtree* qt);

#endif
