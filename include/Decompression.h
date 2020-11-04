#ifndef __DECOMPRESSION__
#define __DECOMPRESSION__

#include "Quadtree.h"

/**
 * Decompress a file called 'file_name' and translate
 * its content into a Quadtree.
 * @return 1 if executed correctly else 0.
 */
int decompression(char* file_name, Quadtree* qt, int display_type);

#endif
