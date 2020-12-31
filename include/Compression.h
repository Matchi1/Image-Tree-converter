#ifndef __COMPRESSION__
#define __COMPRESSION__	

#include "Quadtree.h"
#include "BitFile.h"

/**
 * Compression of a Quadtree and the compression in
 * a file named file_name.
 * @return 1 if executed correctly else 0.
 */
int compression(char* file_name, Quadtree qt);

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

/**
 * Write the specified padding into a file contained in BitFile
 * @parameters out a pointor to a BitFile Structure
 * 			   padding the specified padding
 * @return 0 if the padding is too big else 1
 */
int write_padding(BitFile* out, int padding);

/**
 * Write the bit representing the black or white color
 * depending on the specified color in the Node structure
 * @parameters out a pointor to a BitFile structure
 * 			   color an array representing rgba color
 */
void write_B_W(BitFile* out, int* color);

/**
 * Write the bits representing the specified unite color
 * into a file contained in the BitFile structure
 * @parameters out a pointor to a BitFile structure
 * 			   unite the specified unite color
 */
void write_unite(BitFile* out, int unite);

/**
 * Write the bits representing the specified color
 * into a file contained in the BitFile structure
 * @parameters out a pointor to a BitFile structure
 * 			   color an array representing rgba color
 */
void write_rgba(BitFile* out, int* color);

/**
 * Write the bits representing a tree depending on the prefix browse
 * into a file contained in the bitFile structure
 * It writes the black & white version of this tree
 * @parameters out a pointor to a BitFile structure
 * 			   qt a Quadtree structure
 * 			   bw value representing how to convert the image's color (rgba or black and white)
 */
void prefix(BitFile* out, Quadtree qt, void (*write_color)(BitFile* out, int* color));

#endif
