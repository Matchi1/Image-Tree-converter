#ifndef __COMPRESSION__
#define __COMPRESSION__	

#include "Quadtree.h"

/**
 * Compression of a Quadtree and the compression in
 * a file named file_name.
 * @return 1 if executed correctly else 0.
 */
int compression(char* file_name, Quadtree qt);

/**
 * Compression of a Quadtree and the compression in
 * a file named file_name for black and white image.
 * @return 1 if executed correctly else 0.
 */
int compression_B_W(char* file_name, Quadtree qt);

/**
 * Compression of a Quadtree and the compression in
 * a file named file_name for rgba image.
 * @return 1 if executed correctly else 0.
 */
int compression_Color(char* file_name, Quadtree qt);

/**
 * Count the number of bit a Quadtree will generate during
 * compression.
 * @argument qt a Quadtree
 *           len_bits a pointor containing the number of bits
 *           display_color number representing the format of compression
 *           (compression for colored image or black & white image)
 * @return void
 */
void count_bit(Quadtree qt, int* len_bits, int display_color);


#endif
