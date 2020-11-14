#ifndef __INPUT_IMG__
#define __INPUT_IMG__

#include "Quadtree.h"

/**
 * Convert an image into a Quadtree.
 * @parameters file_name the name of the file.
 * 			   qt a pointor to a Quadtree.
 * @return 1 if the conversion was successeful else 0.
 */
int convert_img_qt(char* file_name, Quadtree* qt);

#endif
