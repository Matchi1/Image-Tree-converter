#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "../include/Extension.h"
#include "../include/Decompression.h"
#include "../include/BitFile.h"
#include "../include/Color.h"

/**
 * Count the number of bits in a specified file
 * @param file_name the name of the specified file
 * @return the number of bits in the file
 */
int count_bit_file(char* file_name){
	int bits;
	FILE* file;

	file = fopen(file_name, "r");
	bits = 0;
	fseek(file, 0, SEEK_SET);
	while(fgetc(file) != EOF)
		bits += 8;
	fclose(file);
	return bits;
}

/**
 * Read the value of the padding in a file
 * @param in a pointor to a BitFile structure
 * @return the padding
 */
int read_padding(BitFile* in){
	int i, padding, bit;
	assert(in != NULL);

	padding = 0;
	for(i = 2; i >= 0; i--){
		bit = read_BitFile(in);
		if(bit == 1)
			padding += pow(2, i);
	}
	return padding;
}

/**
 * Read the next bit in the file and determine
 * the color according to this bit
 * @param in a pointor to a BitFile structure
 * @return the color represented by an array
 */
int* read_B_W(BitFile* in){
	int bit = read_BitFile(in);

	if(bit == 1)
		return create_color(0, 0, 0, 255);
	else
		return create_color(255, 255, 255, 255);
}

/**
 * Read the next byte in a file and determine
 * a unite color depending on this byte
 * @param in a pointor to a BitFile structure
 *    	  unite a pointor to an int value
 * @return EOF if an IO error occurred else 1
 */
int read_unite(BitFile* in, int* unite){
	int i, bit;

	for(i = 7; i >= 0; i--){
		bit = read_BitFile(in); 
		if(bit == 1)
			*unite += pow(2, i);
		else if(bit == EOF){
			fprintf(stderr, "problème de lecture\n");
			return EOF;
		}
	}
	return 1;
}

/**
 * Read the next 4 bytes in a file and determine
 * the color depending on those bytes
 * @param in a pointor to a BitFile structure
 * @return NULL if an IO error occurred else the corresponding color
 */
int* read_rgba(BitFile* in){
	int i;
	int* color;

	color = create_color(0, 0, 0, 0);

	for(i = 0; i < 4; i++){
		if(read_unite(in, &(color[i])) == EOF)
			return NULL;
	}
	return color;
}

/**
 * Verify the type of image the program have to decompress
 * a colorful image or a black and white image
 * it is determined through the specified pointor of function
 * @param total_bits a pointor to an int value
 * 		  read_color a pointor to a function
 */
void verify_display_mode(int* total_bits, int* (*read_color)(BitFile* in)){
	if(read_color == read_B_W)
		(*total_bits)--;
	else
		(*total_bits) -= 32;
}

/**
 * Read the whole specified file and fill a Quadtree structure according to this file
 * @param in a pointor a BitFile structure
 * 		  qt a pointor to Quadtree structure
 * 		  total_bits a pointor to an int value
 *		  read_color a pointor to a function
 */
int read_body(BitFile* in, Quadtree* qt, int* total_bits, int* (*read_color)(BitFile* in)){
	int bit;
	int* color;
	assert(qt != NULL);	
	
	if(*total_bits == 0)
		return 1;
	(*total_bits)--;
	bit = read_BitFile(in);
	*qt = create_node(NULL, 0);
	if(bit == 0){
		if(read_body(in, &(*qt)->sonNW, total_bits, read_color) == 0
			|| read_body(in, &(*qt)->sonNE, total_bits, read_color) == 0
			|| read_body(in, &(*qt)->sonSE, total_bits, read_color) == 0
			|| read_body(in, &(*qt)->sonSW, total_bits, read_color) == 0)
			return 0;
	} else if(bit == 1){
		verify_display_mode(total_bits, read_color);
		color = read_color(in);
		if(NULL == color){
			fprintf(stderr, "Not enough memory space\n");
			return 0;
		}
		(*qt)->pixel = create_pixel(0, 0, 1, color);
	} else 
		return 0;
	return 1;
}

int decompression(char* file_name, Quadtree* qt){
	BitFile in;
	int return_val_ext, total_bits, padding;

	assert(qt != NULL);
	assert(file_name != NULL);
	
	return_val_ext = extension_qt(file_name);
	init_BitFile(&in, file_name, "r");
	padding = read_padding(&in);
	total_bits = count_bit_file(file_name) - 3 - padding;
	if(return_val_ext == -1)
		return -1;
	if(return_val_ext == 0)
		read_body(&in, qt, &total_bits, read_rgba);
	 else 
		read_body(&in, qt, &total_bits, read_B_W);
	close_BitFile(&in);
	return 1;
}
